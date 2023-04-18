#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::StreamAdapter;
using elrond::runtime::OStream;
using elrond::interface::Stream;
using Catch::Matchers::ContainsSubstring;
using Catch::Matchers::Matches;

SCENARIO("Test mocked StreamAdapter instances", "[mock][StreamAdapter]")
{
    std::ostringstream oss;
    OStream stream(oss);

    GIVEN("A custom instance of StreamAdapter")
    {
        StreamAdapter adapter(
            stream,
            [](const Stream& s) { s << "PRE-APPEND"; },
            [](const Stream& s) { s << "POST-APPEND"; }
        );

        WHEN("Call info stream getter")
        {
            auto& s = adapter.stream();
            THEN("The returned info stream object must be the same object passed to adapter constructor")
            {
                CHECK(&s == &stream);
            }
        }

        WHEN("Call pre append operation")
        {
            adapter.preAppend();
            THEN("The string in StringStream should equal to 'PRE-APPEND'")
            {
                CHECK(oss.str() == "PRE-APPEND");
            }
        }

        WHEN("Call post append operation")
        {
            adapter.postAppend();
            THEN("The string in StringStream should equal to 'POST-APPEND'")
            {
                CHECK(oss.str() == "POST-APPEND");
            }
        }
    }

    GIVEN("An instance made by StreamAdapter::makePretty()")
    {
        auto adapter = StreamAdapter::makePretty(stream, "TEST");

        WHEN("Call info stream getter")
        {
            auto& s = adapter->stream();
            THEN("The returned info stream object must be the same object passed to adapter constructor")
            {
                CHECK(&s == &stream);
            }
        }

        WHEN("Call pre append operation")
        {
            adapter->preAppend();
            THEN("The string in StringStream should contains the same tag string")
            {
                CHECK_THAT(oss.str(), ContainsSubstring("TEST"));
            }

            AND_THEN("The string capured in StringStream should be a string with expected pattern")
            {
                CHECK_THAT(oss.str(), Matches("\\[.*\\]\\t"));
            }
        }

        WHEN("Call post append operation")
        {
            adapter->postAppend();
            THEN("The string capured in StringStream should be a string EOL symbol")
            {
                CHECK(oss.str() == "\n");
            }
        }
    }

    GIVEN("An instance made by StreamAdapter::makeNull()")
    {
        auto adapter = StreamAdapter::makeNull(stream, "TEST");

        WHEN("Call info stream getter")
        {
            auto& s = adapter->stream();
            THEN("The returned info stream object must be the same object passed to adapter constructor")
            {
                CHECK(&s == &stream);
            }
        }

        WHEN("Call pre append operation")
        {
            adapter->preAppend();
            THEN("The string capured in StringStream should be an empty string")
            {
                CHECK(oss.str() == "");
            }
        }

        WHEN("Call post append operation")
        {
            adapter->postAppend();
            THEN("The string capured in StringStream should be an empty string")
            {
                CHECK(oss.str() == "");
            }
        }
    }
}
