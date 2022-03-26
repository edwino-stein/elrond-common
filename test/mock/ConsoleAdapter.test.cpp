#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::ConsoleAdapter;

SCENARIO("Test a mocked console adapter instance", "[mock][ConsoleAdapter]")
{
    GIVEN("A ConsoleAdapter mocked to handle info and error outputs")
    {
        std::ostringstream info, error;
        ConsoleAdapter adapter(
            [&info](std::ostringstream& msg) { info << msg.str(); },
            [&error](std::ostringstream& msg) { error << msg.str(); }
        );

        WHEN("An info message is passed to adapter")
        {
            std::ostringstream oss;
            oss <<  "Info message";
            adapter.info(oss, "TEST");

            THEN("The stream must captured the same string message as info")
            {
                CHECK(info.str() == "Info message");
                CHECK(error.str() == "");
            }
        }

        WHEN("An error message is passed to adapter")
        {
            std::ostringstream oss;
            oss <<  "Error message";
            adapter.error(oss, "TEST");

            THEN("The stream must captured the same string message as error")
            {
                CHECK(info.str() == "");
                CHECK(error.str() == "Error message");
            }
        }
    }

    GIVEN("A ConsoleAdapter mocked with default handling functions")
    {
        ConsoleAdapter adapter;

        WHEN("An info message is passed to adapter")
        {
            std::ostringstream oss;
            oss <<  "Info message";

            try
            {
                adapter.info(oss, "TEST");
                THEN("The adapter does not throw an execption")
                {
                    SUCCEED();
                }
            }
            catch(const std::runtime_error&)
            {
                THEN("The adapter does not throw an execption")
                {
                    FAIL();
                }
            }
        }

        WHEN("An error message is passed to adapter")
        {
            std::ostringstream oss;
            oss <<  "Error message";

            try
            {
                adapter.error(oss, "TEST");
                THEN("Must throw an excption with string captured")
                {
                    FAIL();
                }
            }
            catch (const std::runtime_error& e)
            {
                THEN("Must throw an excption with string captured")
                {
                    CHECK(std::string(e.what()) == "Error message");
                }
            }
        }
    }
}
