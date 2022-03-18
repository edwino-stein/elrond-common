#include <elrond.hpp>
#include "catch2.hpp"

TEST_CASE("Check elrond::strLen() function", "[string]")
{
    CHECK(elrond::strLen(ELROND_STR("Hello World!!!")) == 14);
    CHECK(elrond::strLen(ELROND_STR("")) == 0);
    CHECK(elrond::strLen(ELROND_STR("\0something")) == 0);
}
