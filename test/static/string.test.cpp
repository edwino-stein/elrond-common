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
