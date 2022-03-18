#include <elrond.hpp>
#include "catch2.hpp"

TEST_CASE("Check elrond::strLen() function", "[string]")
{
    CHECK(elrond::strLen(ELROND_STR("Hello World!!!")) == 14);
    CHECK(elrond::strLen(ELROND_STR("")) == 0);
    CHECK(elrond::strLen(ELROND_STR("\0something")) == 0);
}

TEST_CASE("Check elrond::strAt() function", "[string]")
{
    elrond::string str = ELROND_STR("Hello World!!!");

    CHECK(elrond::strAt(str, 0) == 'H');
    CHECK(elrond::strAt(str, 1) == 'e');
    CHECK(elrond::strAt(str, 2) == 'l');
    CHECK(elrond::strAt(str, 3) == 'l');
    CHECK(elrond::strAt(str, 4) == 'o');
    CHECK(elrond::strAt(str, 5) == ' ');
    CHECK(elrond::strAt(str, 6) == 'W');
    CHECK(elrond::strAt(str, 7) == 'o');
    CHECK(elrond::strAt(str, 8) == 'r');
    CHECK(elrond::strAt(str, 9) == 'l');
    CHECK(elrond::strAt(str, 10) == 'd');
    CHECK(elrond::strAt(str, 11) == '!');
    CHECK(elrond::strAt(str, 12) == '!');
    CHECK(elrond::strAt(str, 13) == '!');
}

TEST_CASE("Check elrond::strEq() function", "[string]")
{
    elrond::string str = ELROND_STR("Hello World!!!");

    CHECK(elrond::strEq(str, ELROND_STR("Hello World!!!")));
    CHECK_FALSE(elrond::strEq(str, ELROND_STR("hello world!!!")));
    CHECK_FALSE(elrond::strEq(str, ELROND_STR("Hello World!!")));
    CHECK_FALSE(elrond::strEq(str, ELROND_STR("Hello World!!!!")));

    CHECK(elrond::strEq(str, "Hello World!!!"));
    CHECK_FALSE(elrond::strEq(str, "hello world!!!"));
    CHECK_FALSE(elrond::strEq(str, "Hello World!!"));
    CHECK_FALSE(elrond::strEq(str, "Hello World!!!!"));
}

TEST_CASE("Check elrond::strCmp() function", "[string]")
{
    elrond::string str = ELROND_STR("Hello World!!!");

    CHECK(elrond::strCmp(str, ELROND_STR("Hello World!!!")) == 0);
    CHECK(elrond::strCmp(str, ELROND_STR("hello world!!!")) < 0);
    CHECK(elrond::strCmp(str, ELROND_STR("Hello World!!")) > 0);
    CHECK(elrond::strCmp(str, ELROND_STR("Hello World!!!!")) < 0);

    CHECK(elrond::strCmp(str, "Hello World!!!") == 0);
    CHECK(elrond::strCmp(str, "hello world!!!") < 0);
    CHECK(elrond::strCmp(str, "Hello World!!") > 0);
    CHECK(elrond::strCmp(str, "Hello World!!!!") < 0);
}

TEST_CASE("Check elrond::strCpy() function", "[string]")
{
    elrond::string str = ELROND_STR("Hello World!!!");

    SECTION("Copy the string to a much larger buffer")
    {
        char buffer[16];
        REQUIRE(elrond::strCpy(str, buffer, 16) == 14);
        REQUIRE(buffer[14] == '\0');
        REQUIRE(elrond::strCmp(str, buffer) == 0);
    }

    SECTION("Copy the string to a larger buffer")
    {
        char buffer[15];
        REQUIRE(elrond::strCpy(str, buffer, 15) == 14);
        REQUIRE(buffer[14] == '\0');
        REQUIRE(elrond::strCmp(str, buffer) == 0);
    }

    SECTION("Copy the string to a same size buffer")
    {
        char buffer[14];
        REQUIRE(elrond::strCpy(str, buffer, 14) == 13);
        REQUIRE(buffer[13] == '\0');
        REQUIRE(elrond::strCmp(str, buffer) > 0);
    }

    SECTION("Copy the string to a smaller buffer")
    {
        char buffer[13];
        REQUIRE(elrond::strCpy(str, buffer, 13) == 12);
        REQUIRE(buffer[12] == '\0');
        REQUIRE(elrond::strCmp(str, buffer) > 0);
    }
}
