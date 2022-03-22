#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::Arguments;

SCENARIO("Test a mocked arguments object with a set of values", "[mock][Arguments]")
{
    GIVEN("A mocked arguments instance with a set of values")
    {
        Arguments args;
        args.set("int", 123)
             .set("long", static_cast<long>(0xFFFFFFFFFFFFFFFF))
             .set("bool", false)
             .set("char", 'A')
             .set("double", 123.456)
             .set("cstring", "Hello world c stirng")
             .set("elrondstring", elrond::string("Hello world elrond string"));

        REQUIRE(args.total() == 7);

        WHEN("Try get the argument 'int'")
        {
            REQUIRE(args.exists("int"));
            REQUIRE(args.isInt("int"));
            REQUIRE(!args.isLong("int"));
            REQUIRE(!args.isBool("int"));
            REQUIRE(!args.isChar("int"));
            REQUIRE(!args.isDouble("int"));
            REQUIRE(!args.isString("int"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("int") == 123);
                CHECK(args.asLong("int") == 123);
                CHECK(args.asBool("int"));
                CHECK(args.asChar("int") == '{');
                CHECK(args.asDouble("int") == 123.0);
                CHECK(args.asString("int") == "123");
            }
        }

        WHEN("Try get the argument 'long'")
        {
            REQUIRE(args.exists("long"));
            REQUIRE(!args.isInt("long"));
            REQUIRE(args.isLong("long"));
            REQUIRE(!args.isBool("long"));
            REQUIRE(!args.isChar("long"));
            REQUIRE(!args.isDouble("long"));
            REQUIRE(!args.isString("long"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("long") == -1);
                CHECK(args.asLong("long") == static_cast<long>(0xFFFFFFFFFFFFFFFF));
                CHECK(args.asBool("long"));
                CHECK(args.asChar("long") == static_cast<char>(0xFFFFFFFFFFFFFFFF));
                CHECK(args.asDouble("long") == -1.0);
                CHECK(args.asString("long") == "-1");
            }
        }

        WHEN("Try get the argument 'bool'")
        {
            REQUIRE(args.exists("bool"));
            REQUIRE(!args.isInt("bool"));
            REQUIRE(!args.isLong("bool"));
            REQUIRE(args.isBool("bool"));
            REQUIRE(!args.isChar("bool"));
            REQUIRE(!args.isDouble("bool"));
            REQUIRE(!args.isString("bool"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("bool") == 0);
                CHECK(args.asLong("bool") == 0);
                CHECK(!args.asBool("bool"));
                CHECK(args.asChar("bool") == 'f');
                CHECK(args.asDouble("bool") == 0.0);
                CHECK(args.asString("bool") == "false");
            }
        }

        WHEN("Try get the argument 'char'")
        {
            REQUIRE(args.exists("char"));
            REQUIRE(!args.isInt("char"));
            REQUIRE(!args.isLong("char"));
            REQUIRE(!args.isBool("char"));
            REQUIRE(args.isChar("char"));
            REQUIRE(!args.isDouble("char"));
            REQUIRE(!args.isString("char"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("char") == 65);
                CHECK(args.asLong("char") == 65);
                CHECK(args.asBool("char"));
                CHECK(args.asChar("char") == 'A');
                CHECK(args.asDouble("char") == 65.0);
                CHECK(args.asString("char") == "A");
            }
        }

        WHEN("Try get the argument 'double'")
        {
            REQUIRE(args.exists("double"));
            REQUIRE(!args.isInt("double"));
            REQUIRE(!args.isLong("double"));
            REQUIRE(!args.isBool("double"));
            REQUIRE(!args.isChar("double"));
            REQUIRE(args.isDouble("double"));
            REQUIRE(!args.isString("double"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("double") == 123);
                CHECK(args.asLong("double") == 123);
                CHECK(args.asBool("double"));
                CHECK(args.asChar("double") == '{');
                CHECK(args.asDouble("double") == 123.456);
                CHECK(args.asString("double") == "123.456000");
            }
        }

        WHEN("Try get the argument 'cstring'")
        {
            REQUIRE(args.exists("cstring"));
            REQUIRE(!args.isInt("cstring"));
            REQUIRE(!args.isLong("cstring"));
            REQUIRE(!args.isBool("cstring"));
            REQUIRE(!args.isChar("cstring"));
            REQUIRE(!args.isDouble("cstring"));
            REQUIRE(args.isString("cstring"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("cstring") == 0);
                CHECK(args.asLong("cstring") == 0);
                CHECK(args.asBool("cstring"));
                CHECK(args.asChar("cstring") == 'H');
                CHECK(args.asDouble("cstring") == 0);
                CHECK(args.asString("cstring") == "Hello world c stirng");
            }
        }

        WHEN("Try get the argument 'elrondstring'")
        {
            REQUIRE(args.exists("elrondstring"));
            REQUIRE(!args.isInt("elrondstring"));
            REQUIRE(!args.isLong("elrondstring"));
            REQUIRE(!args.isBool("elrondstring"));
            REQUIRE(!args.isChar("elrondstring"));
            REQUIRE(!args.isDouble("elrondstring"));
            REQUIRE(args.isString("elrondstring"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("elrondstring") == 0);
                CHECK(args.asLong("elrondstring") == 0);
                CHECK(args.asBool("elrondstring"));
                CHECK(args.asChar("elrondstring") == 'H');
                CHECK(args.asDouble("elrondstring") == 0);
                CHECK(args.asString("elrondstring") == "Hello world elrond string");
            }
        }

        WHEN("Try get an invalid argument")
        {
            REQUIRE(!args.exists("null"));
            REQUIRE(!args.isInt("null"));
            REQUIRE(!args.isLong("null"));
            REQUIRE(!args.isBool("null"));
            REQUIRE(!args.isChar("null"));
            REQUIRE(!args.isDouble("null"));
            REQUIRE(!args.isString("null"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(args.asInt("null") == 0);
                CHECK(args.asLong("null") == 0);
                CHECK(!args.asBool("null"));
                CHECK(args.asChar("null") == '\0');
                CHECK(args.asDouble("null") == 0);
                CHECK(args.asString("null") == "");
            }
        }
    }
}
