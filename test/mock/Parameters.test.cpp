#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::Parameters;

SCENARIO("Test a mocked parameters with a set of values", "[mock][Console]")
{
    GIVEN("A mocked Parameters instance with a set of values")
    {
        Parameters param;
        param.set("int", 123)
             .set("long", static_cast<long>(0xFFFFFFFFFFFFFFFF))
             .set("bool", false)
             .set("char", 'A')
             .set("double", 123.456)
             .set("cstring", "Hello world c stirng")
             .set("elrondstring", elrond::string("Hello world elrond string"));

        REQUIRE(param.total() == 7);

        WHEN("Try get the param 'int'")
        {
            REQUIRE(param.exists("int"));
            REQUIRE(param.isInt("int"));
            REQUIRE(!param.isLong("int"));
            REQUIRE(!param.isBool("int"));
            REQUIRE(!param.isChar("int"));
            REQUIRE(!param.isDouble("int"));
            REQUIRE(!param.isString("int"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("int") == 123);
                CHECK(param.asLong("int") == 123);
                CHECK(param.asBool("int"));
                CHECK(param.asChar("int") == '{');
                CHECK(param.asDouble("int") == 123.0);
                CHECK(param.asString("int") == "123");
            }
        }

        WHEN("Try get the param 'long'")
        {
            REQUIRE(param.exists("long"));
            REQUIRE(!param.isInt("long"));
            REQUIRE(param.isLong("long"));
            REQUIRE(!param.isBool("long"));
            REQUIRE(!param.isChar("long"));
            REQUIRE(!param.isDouble("long"));
            REQUIRE(!param.isString("long"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("long") == -1);
                CHECK(param.asLong("long") == static_cast<long>(0xFFFFFFFFFFFFFFFF));
                CHECK(param.asBool("long"));
                CHECK(param.asChar("long") == static_cast<char>(0xFFFFFFFFFFFFFFFF));
                CHECK(param.asDouble("long") == -1.0);
                CHECK(param.asString("long") == "-1");
            }
        }

        WHEN("Try get the param 'bool'")
        {
            REQUIRE(param.exists("bool"));
            REQUIRE(!param.isInt("bool"));
            REQUIRE(!param.isLong("bool"));
            REQUIRE(param.isBool("bool"));
            REQUIRE(!param.isChar("bool"));
            REQUIRE(!param.isDouble("bool"));
            REQUIRE(!param.isString("bool"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("bool") == 0);
                CHECK(param.asLong("bool") == 0);
                CHECK(!param.asBool("bool"));
                CHECK(param.asChar("bool") == 'f');
                CHECK(param.asDouble("bool") == 0.0);
                CHECK(param.asString("bool") == "false");
            }
        }

        WHEN("Try get the param 'char'")
        {
            REQUIRE(param.exists("char"));
            REQUIRE(!param.isInt("char"));
            REQUIRE(!param.isLong("char"));
            REQUIRE(!param.isBool("char"));
            REQUIRE(param.isChar("char"));
            REQUIRE(!param.isDouble("char"));
            REQUIRE(!param.isString("char"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("char") == 65);
                CHECK(param.asLong("char") == 65);
                CHECK(param.asBool("char"));
                CHECK(param.asChar("char") == 'A');
                CHECK(param.asDouble("char") == 65.0);
                CHECK(param.asString("char") == "A");
            }
        }

        WHEN("Try get the param 'double'")
        {
            REQUIRE(param.exists("double"));
            REQUIRE(!param.isInt("double"));
            REQUIRE(!param.isLong("double"));
            REQUIRE(!param.isBool("double"));
            REQUIRE(!param.isChar("double"));
            REQUIRE(param.isDouble("double"));
            REQUIRE(!param.isString("double"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("double") == 123);
                CHECK(param.asLong("double") == 123);
                CHECK(param.asBool("double"));
                CHECK(param.asChar("double") == '{');
                CHECK(param.asDouble("double") == 123.456);
                CHECK(param.asString("double") == "123.456000");
            }
        }

        WHEN("Try get the param 'cstring'")
        {
            REQUIRE(param.exists("cstring"));
            REQUIRE(!param.isInt("cstring"));
            REQUIRE(!param.isLong("cstring"));
            REQUIRE(!param.isBool("cstring"));
            REQUIRE(!param.isChar("cstring"));
            REQUIRE(!param.isDouble("cstring"));
            REQUIRE(param.isString("cstring"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("cstring") == 0);
                CHECK(param.asLong("cstring") == 0);
                CHECK(param.asBool("cstring"));
                CHECK(param.asChar("cstring") == 'H');
                CHECK(param.asDouble("cstring") == 0);
                CHECK(param.asString("cstring") == "Hello world c stirng");
            }
        }

        WHEN("Try get the param 'elrondstring'")
        {
            REQUIRE(param.exists("elrondstring"));
            REQUIRE(!param.isInt("elrondstring"));
            REQUIRE(!param.isLong("elrondstring"));
            REQUIRE(!param.isBool("elrondstring"));
            REQUIRE(!param.isChar("elrondstring"));
            REQUIRE(!param.isDouble("elrondstring"));
            REQUIRE(param.isString("elrondstring"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("elrondstring") == 0);
                CHECK(param.asLong("elrondstring") == 0);
                CHECK(param.asBool("elrondstring"));
                CHECK(param.asChar("elrondstring") == 'H');
                CHECK(param.asDouble("elrondstring") == 0);
                CHECK(param.asString("elrondstring") == "Hello world elrond string");
            }
        }

        WHEN("Try get an invalid param")
        {
            REQUIRE(!param.exists("null"));
            REQUIRE(!param.isInt("null"));
            REQUIRE(!param.isLong("null"));
            REQUIRE(!param.isBool("null"));
            REQUIRE(!param.isChar("null"));
            REQUIRE(!param.isDouble("null"));
            REQUIRE(!param.isString("null"));

            THEN("Must resturns the expected values as eath type")
            {
                CHECK(param.asInt("null") == 0);
                CHECK(param.asLong("null") == 0);
                CHECK(!param.asBool("null"));
                CHECK(param.asChar("null") == '\0');
                CHECK(param.asDouble("null") == 0);
                CHECK(param.asString("null") == "");
            }
        }
    }
}
