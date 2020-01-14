#include "elrond-test.hpp"

TEST_CASE("Bitwise functions for Elrond Test Library", "[bitwise],[runtime]" )
{
    REQUIRE(elrond::highByte(0xABCD) == 0xAB);
    REQUIRE(elrond::highByte(0xCD) == 0x00);
    REQUIRE(elrond::lowByte(0xABCD) == 0xCD);
    REQUIRE(elrond::lowByte(0xABCD) == 0xCD);
    REQUIRE(elrond::makeWord(0xAB, 0xCD) == 0xABCD);

    REQUIRE(elrond::highWord(0x1234ABCD) == 0x1234);
    REQUIRE(elrond::lowWord(0x1234ABCD) == 0xABCD);
    REQUIRE(elrond::makeDWord(0x1234, 0xABCD) == 0x1234ABCD);
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
