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
