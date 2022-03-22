#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::Arguments;

SCENARIO("Test a mocked arguments object with a set of values", "[mock][Arguments]")
{
    GIVEN("A mocked arguments instance with a set of values")
    {
        Arguments args;
        args.set("int", 123)
             .set("sint", -1)
             .set("uint", static_cast<unsigned int>(-1))
             .set("bool", false)
             .set("double", 123.456)
             .set("cstring", "Hello world c stirng")
             .set("elrondstring", ELROND_STR("Hello world elrond string"));

        REQUIRE(args.total() == 7);

        WHEN("Try get the argument 'int'")
        {
            REQUIRE(args.exists("int"));
            REQUIRE(args.isInt("int"));
            REQUIRE_FALSE(args.isUInt("int"));
            REQUIRE_FALSE(args.isBool("int"));
            REQUIRE_FALSE(args.isDouble("int"));
            REQUIRE_FALSE(args.isString("int"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("int") == 123);
                CHECK(args.asUInt("int") == 123);
                CHECK(args.asBool("int"));
                CHECK(args.asDouble("int") == 123.0);
                CHECK(args.asString("int") == "123");
            }
        }

        WHEN("Try get the argument 'sint'")
        {
            REQUIRE(args.exists("sint"));
            REQUIRE(args.isInt("sint"));
            REQUIRE_FALSE(args.isUInt("sint"));
            REQUIRE_FALSE(args.isBool("sint"));
            REQUIRE_FALSE(args.isDouble("sint"));
            REQUIRE_FALSE(args.isString("sint"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("sint") == -1);
                CHECK(args.asUInt("sint") == static_cast<unsigned int>(0xFFFFFFFFFFFFFFFF));
                CHECK(args.asBool("sint"));
                CHECK(args.asDouble("sint") == -1.0);
                CHECK(args.asString("sint") == "-1");
            }
        }

        WHEN("Try get the argument 'uint'")
        {
            REQUIRE(args.exists("uint"));
            REQUIRE_FALSE(args.isInt("uint"));
            REQUIRE(args.isUInt("uint"));
            REQUIRE_FALSE(args.isBool("uint"));
            REQUIRE_FALSE(args.isDouble("uint"));
            REQUIRE_FALSE(args.isString("uint"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("uint") == -1);
                CHECK(args.asUInt("uint") == static_cast<unsigned int>(0xFFFFFFFFFFFFFFFF));
                CHECK(args.asBool("uint"));
                CHECK(args.asDouble("uint") == 4294967295.0);
                CHECK(args.asString("uint") == "4294967295");
            }
        }

        WHEN("Try get the argument 'bool'")
        {
            REQUIRE(args.exists("bool"));
            REQUIRE_FALSE(args.isInt("bool"));
            REQUIRE_FALSE(args.isUInt("bool"));
            REQUIRE(args.isBool("bool"));
            REQUIRE_FALSE(args.isDouble("bool"));
            REQUIRE_FALSE(args.isString("bool"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("bool") == 0);
                CHECK(args.asUInt("bool") == 0);
                CHECK_FALSE(args.asBool("bool"));
                CHECK(args.asDouble("bool") == 0.0);
                CHECK(args.asString("bool") == "false");
            }
        }

        WHEN("Try get the argument 'double'")
        {
            REQUIRE(args.exists("double"));
            REQUIRE_FALSE(args.isInt("double"));
            REQUIRE_FALSE(args.isUInt("double"));
            REQUIRE_FALSE(args.isBool("double"));
            REQUIRE(args.isDouble("double"));
            REQUIRE_FALSE(args.isString("double"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("double") == 123);
                CHECK(args.asUInt("double") == 123);
                CHECK(args.asBool("double"));
                CHECK(args.asDouble("double") == 123.456);
                CHECK(args.asString("double") == "123.456000");
            }
        }

        WHEN("Try get the argument 'cstring'")
        {
            REQUIRE(args.exists("cstring"));
            REQUIRE_FALSE(args.isInt("cstring"));
            REQUIRE_FALSE(args.isUInt("cstring"));
            REQUIRE_FALSE(args.isBool("cstring"));
            REQUIRE_FALSE(args.isDouble("cstring"));
            REQUIRE(args.isString("cstring"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("cstring") == 0);
                CHECK(args.asUInt("cstring") == 0);
                CHECK_FALSE(args.asBool("cstring"));
                CHECK(args.asDouble("cstring") == 0);
                CHECK(args.asString("cstring") == "Hello world c stirng");
            }
        }

        WHEN("Try get the argument 'elrondstring'")
        {
            REQUIRE(args.exists("elrondstring"));
            REQUIRE_FALSE(args.isInt("elrondstring"));
            REQUIRE_FALSE(args.isUInt("elrondstring"));
            REQUIRE_FALSE(args.isBool("elrondstring"));
            REQUIRE_FALSE(args.isDouble("elrondstring"));
            REQUIRE(args.isString("elrondstring"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("elrondstring") == 0);
                CHECK(args.asUInt("elrondstring") == 0);
                CHECK_FALSE(args.asBool("elrondstring"));
                CHECK(args.asDouble("elrondstring") == 0);
                CHECK(args.asString("elrondstring") == "Hello world elrond string");
            }
        }

        WHEN("Try get an invalid argument")
        {
            REQUIRE_FALSE(args.exists("null"));
            REQUIRE_FALSE(args.isInt("null"));
            REQUIRE_FALSE(args.isUInt("null"));
            REQUIRE_FALSE(args.isBool("null"));
            REQUIRE_FALSE(args.isDouble("null"));
            REQUIRE_FALSE(args.isString("null"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("null") == 0);
                CHECK(args.asUInt("null") == 0);
                CHECK_FALSE(args.asBool("null"));
                CHECK(args.asDouble("null") == 0);
                CHECK(args.asString("null") == "");
            }
        }

        WHEN("Clear the arguments set")
        {
            args.clear();

            THEN("Must resturns the expected values as eath type")
            {
                REQUIRE(args.total() == 0);

                CHECK_FALSE(args.exists("int"));
                CHECK_FALSE(args.exists("sint"));
                CHECK_FALSE(args.exists("uint"));
                CHECK_FALSE(args.exists("bool"));
                CHECK_FALSE(args.exists("double"));
                CHECK_FALSE(args.exists("cstring"));
                CHECK_FALSE(args.exists("elrondstring"));
            }
        }
    }
}
