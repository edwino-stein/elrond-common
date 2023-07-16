#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::interface::Stream;
using elrond::runtime::OStream;
using elrond::runtime::NullStream;
using elrond::mock::StreamAdapter;
using SEVERITY = elrond::interface::ConsoleAdapter::SEVERITY;
using elrond::mock::SeverityToStr;

SCENARIO("Test mocked console adapter instances", "[mock][ConsoleAdapter]")
{
    std::ostringstream oss;

    GIVEN("A ConsoleAdapter mocked with only stream maker function")
    {
        ConsoleAdapter adapter([&oss](){ return std::make_shared<OStream>(oss); });

        WHEN("Call stream maker function")
        {
            auto stream = adapter.makeStream();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<OStream>(stream.get()));
            }

            AND_THEN("The pre append operation should do nothing")
            {
                adapter.preAppend(*stream, "NONE", SEVERITY::INFO);
                CHECK(oss.str() == "");
            }

            AND_THEN("The post append operation should do nothing")
            {
                adapter.postAppend(*stream, "NONE", SEVERITY::INFO);
                CHECK(oss.str() == "");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked an pre append function")
    {
        ConsoleAdapter adapter(
            [&oss](){ return std::make_shared<OStream>(oss); },
            [](Stream& s, const elrond::string& tag, ConsoleAdapter::SEVERITY severity)
            { s << "PRE-APPEND(" << tag << ", " << SeverityToStr(severity) << ')'; }
        );

        WHEN("Call stream maker function")
        {
            auto stream = adapter.makeStream();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<OStream>(stream.get()));
            }

            AND_THEN("The pre append operation should append the expected string")
            {
                adapter.preAppend(*stream, "NONE", SEVERITY::INFO);
                CHECK(oss.str() == "PRE-APPEND(NONE, INFO)");
            }

            AND_THEN("The post append operation should do nothing")
            {
                adapter.postAppend(*stream, "NONE", SEVERITY::INFO);
                CHECK(oss.str() == "");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked an pre append and post append functions")
    {
        ConsoleAdapter adapter(
            [&oss](){ return std::make_shared<OStream>(oss); },
            [](Stream& s, const elrond::string& tag, ConsoleAdapter::SEVERITY severity)
            { s << "PRE-APPEND(" << tag << ", " << SeverityToStr(severity) << ')'; },
            [](Stream& s, const elrond::string& tag, ConsoleAdapter::SEVERITY severity)
            { s << "POST-APPEND(" << tag << ", " << SeverityToStr(severity) << ')'; }
        );

        WHEN("Call stream maker function")
        {
            auto stream = adapter.makeStream();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<OStream>(stream.get()));
            }

            AND_THEN("The pre append operation should append the expected string")
            {
                adapter.preAppend(*stream, "NONE", SEVERITY::INFO);
                CHECK(oss.str() == "PRE-APPEND(NONE, INFO)");
            }

            AND_THEN("The post append operation should do nothing")
            {
                adapter.postAppend(*stream, "NONE", SEVERITY::INFO);
                CHECK(oss.str() == "POST-APPEND(NONE, INFO)");
            }
        }
    }
}

SCENARIO("Test mocked console adapter null instances", "[mock][ConsoleAdapter]")
{
    GIVEN("The ConsoleAdapter::null() instance")
    {
        auto& adapter = ConsoleAdapter::null();

        WHEN("Call stream maker function")
        {
            auto stream = adapter.makeStream();

            THEN("The returned info adapter object should be an intance of runtime::NullStream")
            {
                CHECK(isInstanceOf<NullStream>(stream.get()));
            }
        }
    }
}
