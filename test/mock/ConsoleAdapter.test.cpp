#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::interface::Stream;
using elrond::runtime::OStream;
using elrond::runtime::NullStream;
using elrond::mock::StreamAdapter;

SCENARIO("Test mocked console adapter instances", "[mock][ConsoleAdapter]")
{
    std::ostringstream oss;
    OStream stream(oss);

    GIVEN("A ConsoleAdapter mocked with default constructor")
    {
        ConsoleAdapter adapter(stream);

        WHEN("Call info stream adapter getter")
        {
            auto infoAdapter = adapter.getInfoStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(infoAdapter.get()));
            }

            AND_THEN("The stream object should be the same object passed to constructor")
            {
                auto& s = infoAdapter->stream();
                CHECK(&s == &stream);
            }

            AND_THEN("The pre append operation should do nothing")
            {
                infoAdapter->preAppend();
                CHECK(oss.str() == "");
            }

            AND_THEN("The post append operation should do nothing")
            {
                infoAdapter->preAppend();
                CHECK(oss.str() == "");
            }
        }

        WHEN("Call error stream adapter getter")
        {
            auto errorAdapter = adapter.getErrorStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(errorAdapter.get()));
            }

            AND_THEN("The stream object should be the same object passed to constructor")
            {
                auto& s = errorAdapter->stream();
                CHECK(&s == &stream);
            }

            AND_THEN("The pre append operation should do nothing")
            {
                errorAdapter->preAppend();
                CHECK(oss.str() == "");
            }

            AND_THEN("The post append operation should do nothing")
            {
                errorAdapter->postAppend();
                CHECK(oss.str() == "");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked passing the mock::StreamAdapter::makePretty function to constructor")
    {
        ConsoleAdapter adapter(stream, StreamAdapter::makePretty);

        WHEN("Call info stream adapter getter")
        {
            auto infoAdapter = adapter.getInfoStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(infoAdapter.get()));
            }

            AND_THEN("The stream object should be the same object passed to constructor")
            {
                auto& s = infoAdapter->stream();
                CHECK(&s == &stream);
            }

            AND_THEN("The pre append operation should append the expected string")
            {
                infoAdapter->preAppend();
                CHECK(oss.str() == "[INFO]\t");
            }

            AND_THEN("The pre append operation should append an EOL symbol")
            {
                infoAdapter->postAppend();
                CHECK(oss.str() == "\n");
            }
        }

        WHEN("Call error stream adapter getter")
        {
            auto errorAdapter = adapter.getErrorStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(errorAdapter.get()));
            }

            AND_THEN("The stream object should be the same object passed to constructor")
            {
                auto& s = errorAdapter->stream();
                CHECK(&s == &stream);
            }

            AND_THEN("The pre append operation should append the expected string")
            {
                errorAdapter->preAppend();
                CHECK(oss.str() == "[ERROR]\t");
            }

            AND_THEN("The pre append operation should append an EOL symbol")
            {
                errorAdapter->postAppend();
                CHECK(oss.str() == "\n");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked passing a custrom mock::StreamAdapter factory function to constructor")
    {
        ConsoleAdapter adapter(
            stream,
            [](Stream& stream, elrond::string tag)
            {
                return std::make_shared<StreamAdapter>(
                    stream,
                    [tag](const Stream& s) { s << "PRE-APPEND(" << tag << ")"; },
                    [tag](const Stream& s) { s << "POST-APPEND(" << tag << ")"; }
                );
            }
        );

        WHEN("Call info stream adapter getter")
        {
            auto infoAdapter = adapter.getInfoStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(infoAdapter.get()));
            }

            AND_THEN("The stream object should be the same object passed to constructor")
            {
                auto& s = infoAdapter->stream();
                CHECK(&s == &stream);
            }

            AND_THEN("The pre append operation should append the expected string")
            {
                infoAdapter->preAppend();
                CHECK(oss.str() == "PRE-APPEND(INFO)");
            }

            AND_THEN("The pre append operation should append an EOL symbol")
            {
                infoAdapter->postAppend();
                CHECK(oss.str() == "POST-APPEND(INFO)");
            }
        }

        WHEN("Call error stream adapter getter")
        {
            auto errorAdapter = adapter.getErrorStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(errorAdapter.get()));
            }

            AND_THEN("The stream object should be the same object passed to constructor")
            {
                auto& s = errorAdapter->stream();
                CHECK(&s == &stream);
            }

            AND_THEN("The pre append operation should append the expected string")
            {
                errorAdapter->preAppend();
                CHECK(oss.str() == "PRE-APPEND(ERROR)");
            }

            AND_THEN("The pre append operation should append an EOL symbol")
            {
                errorAdapter->postAppend();
                CHECK(oss.str() == "POST-APPEND(ERROR)");
            }
        }
    }
}

SCENARIO("Test mocked console adapter null instances", "[mock][ConsoleAdapter]")
{
    GIVEN("The ConsoleAdapter::null() instance")
    {
        ConsoleAdapter* adapter = ConsoleAdapter::null();

        WHEN("Call info stream adapter getter")
        {
            auto infoAdapter = adapter->getInfoStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(infoAdapter.get()));
            }

            AND_THEN("The returned info stream must be an intance of NullStream")
            {
                CHECK(isInstanceOf<NullStream>(infoAdapter->stream()));
            }
        }

        WHEN("Call error stream adapter getter")
        {
            auto errorAdapter = adapter->getErrorStreamAdapter();

            THEN("The returned info adapter object should be an intance of mock::StreamAdapter")
            {
                CHECK(isInstanceOf<StreamAdapter>(errorAdapter.get()));
            }

            AND_THEN("The returned info stream must be an intance of NullStream")
            {
                CHECK(isInstanceOf<NullStream>(errorAdapter->stream()));
            }
        }
    }
}
