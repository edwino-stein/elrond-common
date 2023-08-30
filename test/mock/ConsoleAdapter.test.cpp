#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::interface::Stream;
using elrond::runtime::OStream;
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
                CHECK(isInstanceOf<OStream>(csa->stream()));
            }

            THEN("The pre append operation should do nothing")
            {
                csa->preAppend(elrond::SEVERITY::INFO);
                CHECK(oss.str() == "");
            }

            THEN("The post append operation should do nothing")
            {
                csa->postAppend(elrond::SEVERITY::INFO);
                CHECK(oss.str() == "");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked an pre append function")
    {
        ConsoleAdapter consoleAdapter(
            [&oss](){ return std::make_shared<OStream>(oss); },
            [](IConsoleStreamAdapter& a, elrond::SEVERITY severity)
            { a.stream() << "PRE-APPEND(" << SeverityToStr(severity) << ')'; }
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
                CHECK(isInstanceOf<OStream>(csa->stream()));
            }

            THEN("The pre append operation should do nothing")
            {
                csa->preAppend(elrond::SEVERITY::INFO);
                CHECK(oss.str() == "PRE-APPEND(INFO)");
            }

            THEN("The post append operation should do nothing")
            {
                csa->postAppend(elrond::SEVERITY::INFO);
                CHECK(oss.str() == "");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked an pre append and post append functions")
    {
        ConsoleAdapter consoleAdapter(
            [&oss](){ return std::make_shared<OStream>(oss); },
            [](IConsoleStreamAdapter& a, elrond::SEVERITY severity)
            { a.stream() << "PRE-APPEND(" << SeverityToStr(severity) << ')'; },
            [](IConsoleStreamAdapter& a, elrond::SEVERITY severity)
            { a.stream() << "POST-APPEND(" << SeverityToStr(severity) << ')'; }
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
                CHECK(isInstanceOf<OStream>(csa->stream()));
            }

            THEN("The pre append operation should do nothing")
            {
                csa->preAppend(elrond::SEVERITY::INFO);
                CHECK(oss.str() == "PRE-APPEND(INFO)");
            }

            AND_THEN("The post append operation should do nothing")
            {
                csa->postAppend(elrond::SEVERITY::INFO);
                CHECK(oss.str() == "POST-APPEND(INFO)");
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
                CHECK(isInstanceOf<NullStream>(csa->stream()));
            }
        }
    }
}
