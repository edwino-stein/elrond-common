#include "elrond-test.hpp"
#include "catch.hpp"

TEST_CASE("Bitwise functions for Elrond Test Library")
{
    CHECK(elrond::highByte(0xABCD) == 0xAB);
    CHECK(elrond::highByte(0xCD) == 0x00);
    CHECK(elrond::lowByte(0xABCD) == 0xCD);
    CHECK(elrond::lowByte(0xABCD) == 0xCD);
    CHECK(elrond::makeWord(0xAB, 0xCD) == 0xABCD);

    CHECK(elrond::highWord(0x1234ABCD) == 0x1234);
    CHECK(elrond::lowWord(0x1234ABCD) == 0xABCD);
    CHECK(elrond::makeDWord(0x1234, 0xABCD) == 0x1234ABCD);
}

TEST_CASE("Math functions for Elrond Test Library", "[math],[runtime]" )
{
    REQUIRE(elrond::abs(-1) == 1);
    REQUIRE(elrond::abs(1) == 1);
    REQUIRE(elrond::abs(0) == 0);
    REQUIRE(elrond::mod(123.456) == Approx(0.456));
}

TEST_CASE("Time functions for Elrond Test Library", "[time],[runtime]" )
{
    auto now = elrond::millis();
    elrond::delay(100);
    REQUIRE(elrond::millis() >= now + 100);

    now = elrond::micros();
    elrond::delayMicroseconds(100);
    REQUIRE(elrond::micros() >= now + 100);
}
