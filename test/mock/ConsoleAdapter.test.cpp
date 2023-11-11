#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::interface::Stream;
using elrond::runtime::OStream;
using elrond::runtime::OStringStream;
using elrond::runtime::NullStream;
using elrond::mock::ConsoleStreamAdapter;
using elrond::mock::SeverityToStr;
using IConsoleStreamAdapter = elrond::interface::ConsoleStreamAdapter;

SCENARIO("Test mocked console adapter instances", "[mock][ConsoleAdapter]")
{
    std::ostringstream oss;

    GIVEN("A ConsoleAdapter mocked with only stream maker function")
    {
        ConsoleAdapter consoleAdapter([&oss](){ return std::make_shared<OStream>(oss); });

        WHEN("Create a console stream adapter")
        {
            auto csa = consoleAdapter.makeConsoleStreamAdapter();

            THEN("The returned console stream adapter object should be an intance of mock::ConsoleStreamAdapter")
            {
                CHECK(isInstanceOf<ConsoleStreamAdapter>(csa.get()));
            }

            THEN("The stream in console stream adapter should be an instance of runtime::OStream")
            {
                CHECK(isInstanceOf<OStream>(csa->makeStream().get()));
            }

            THEN("The pre append operation should do nothing")
            {
                csa->flush(*(csa->makeStream()), elrond::SEVERITY::INFO);
                CHECK(oss.str() == "");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked an flush function")
    {
        ConsoleAdapter consoleAdapter(
            [](){ return std::make_shared<OStringStream>(); },
            [&oss](Stream& s, elrond::SEVERITY severity)
            { oss << "FLUSH(" << SeverityToStr(severity) << "): " << reinterpret_cast<OStringStream&>(s).oss().str(); }
        );

        WHEN("Create a console stream adapter")
        {
            auto csa = consoleAdapter.makeConsoleStreamAdapter();

            THEN("The returned console stream adapter object should be an intance of mock::ConsoleStreamAdapter")
            {
                CHECK(isInstanceOf<ConsoleStreamAdapter>(csa.get()));
            }

            THEN("The stream in console stream adapter should be an instance of runtime::OStream")
            {
                CHECK(isInstanceOf<OStringStream>(csa->makeStream().get()));
            }

            THEN("The pre append operation should do nothing")
            {
                auto s = csa->makeStream();
                *s << "Test string";
    
                csa->flush(*s, elrond::SEVERITY::INFO);
                CHECK(oss.str() == "FLUSH(INFO): Test string");
            }
        }
    }
}

SCENARIO("Test mocked console adapter null instances", "[mock][ConsoleAdapter]")
{
    GIVEN("The ConsoleAdapter::null() instance")
    {
        auto& consoleAdapter = ConsoleAdapter::null();

        WHEN("Create a console stream adapter")
        {
            auto csa = consoleAdapter.makeConsoleStreamAdapter();

            THEN("The returned console stream adapter object should be an intance of mock::ConsoleStreamAdapter")
            {
                CHECK(isInstanceOf<ConsoleStreamAdapter>(csa.get()));
            }

            THEN("The stream in console stream adapter should be an instance of runtime::NullStream")
            {
                CHECK(isInstanceOf<NullStream>(csa->makeStream().get()));
            }
        }
    }
}
