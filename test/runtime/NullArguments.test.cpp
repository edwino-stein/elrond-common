#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::runtime::NullArguments;

TEST_CASE("Check NullArguments signed integer methods", "[NullArguments]")
{
    NullArguments args;

    CHECK(args.isInt("const char key") == false);
    CHECK(args.asInt("const char key") == elrond::int32());

    CHECK(args.isInt(ELROND_STR("elrond::string key")) == false);
    CHECK(args.asInt(ELROND_STR("elrond::string key")) == elrond::int32());
}

TEST_CASE("Check NullArguments unsigned integer methods", "[NullArguments]")
{
    NullArguments args;

    CHECK(args.isUInt("const char key") == false);
    CHECK(args.asUInt("const char key") == elrond::int32());

    CHECK(args.isUInt(ELROND_STR("elrond::string key")) == false);
    CHECK(args.asUInt(ELROND_STR("elrond::string key")) == elrond::int32());
}

TEST_CASE("Check NullArguments boolean methods", "[NullArguments]")
{
    NullArguments args;

    CHECK(args.isBool("const char key") == false);
    CHECK(args.asBool("const char key") == false);

    CHECK(args.isBool(ELROND_STR("elrond::string key")) == false);
    CHECK(args.asBool(ELROND_STR("elrond::string key")) == false);
}

TEST_CASE("Check NullArguments double methods", "[NullArguments]")
{
    NullArguments args;

    CHECK(args.isDouble("const char key") == false);
    CHECK(args.asDouble("const char key") == double());

    CHECK(args.isDouble(ELROND_STR("elrond::string key")) == false);
    CHECK(args.asDouble(ELROND_STR("elrond::string key")) == double());
}

TEST_CASE("Check NullArguments string methods", "[NullArguments]")
{
    char buffer[10] = {0};
    NullArguments args;

    CHECK(args.isString("const char key") == false);
    CHECK(args.asString("const char key") == elrond::nullstr());
    CHECK(args.asString("const char key", buffer, 10) == 0);
    CHECK(elrond::strEq(buffer, ""));

    CHECK(args.isString(ELROND_STR("elrond::string key")) == false);
    CHECK(args.asString(ELROND_STR("elrond::string key")) == elrond::nullstr());
    CHECK(args.asString(ELROND_STR("elrond::string key"), buffer, 10) == 0);
    CHECK(elrond::strEq(buffer, ""));
}

TEST_CASE("Check NullArguments exists method", "[NullArguments]")
{
    NullArguments args;

    CHECK(args.exists("const char key") == false);
    CHECK(args.exists(ELROND_STR("elrond::string key")) == false);
}
