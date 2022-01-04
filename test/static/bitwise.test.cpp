#include <elrond.hpp>
#include "catch2.hpp"

TEST_CASE("Check elrond::highByte() function", "[bitwise]")
{
    CHECK(elrond::highByte(0xABCD) == 0xAB);
    CHECK(elrond::highByte(0xCD) == 0x0);
    CHECK(elrond::highByte(0x0) == 0x0);
    CHECK(elrond::highByte(-1) == 0xFF);
}

TEST_CASE("Check elrond::lowByte() function", "[bitwise]")
{
    CHECK(elrond::lowByte(0xABCD) == 0xCD);
    CHECK(elrond::lowByte(0xCD) == 0xCD);
    CHECK(elrond::lowByte(0x0) == 0x0);
    CHECK(elrond::lowByte(-1) == 0xFF);
}

TEST_CASE("Check elrond::makeWord() function", "[bitwise]")
{
    CHECK(elrond::makeWord(0xAB, 0xCD) == 0xABCD);
    CHECK(elrond::makeWord(0xCD, 0xAB) == 0xCDAB);
    CHECK(elrond::makeWord(0x0, 0xAB) == 0xAB);
    CHECK(elrond::makeWord(0xAB, 0x0) == 0xAB00);
    CHECK(elrond::makeWord(0x0, 0x0) == 0x0);
    CHECK(elrond::makeWord(-1, 0x0) == 0xFF00);
    CHECK(elrond::makeWord(0x0, -1) == 0xFF);
}

TEST_CASE("Check elrond::highWord() function", "[bitwise]")
{
    CHECK(elrond::highWord(0x1234ABCD) == 0x1234);
    CHECK(elrond::highWord(0xABCD) == 0x0);
    CHECK(elrond::highWord(0x0) == 0x0);
    CHECK(elrond::highWord(-1) == 0xFFFF);
}

TEST_CASE("Check elrond::lowWord() function", "[bitwise]")
{
    CHECK(elrond::lowWord(0x1234ABCD) == 0xABCD);
    CHECK(elrond::lowWord(0xABCD) == 0xABCD);
    CHECK(elrond::lowWord(0x0) == 0x0);
    CHECK(elrond::lowWord(-1) == 0xFFFF);
}

TEST_CASE("Check elrond::makeDWord() function", "[bitwise]")
{
    CHECK(elrond::makeDWord(0x1234, 0xABCD) == 0x1234ABCD);
    CHECK(elrond::makeDWord(0xABCD, 0x1234) == 0xABCD1234);
    CHECK(elrond::makeDWord(0x0, 0xABCD) == 0xABCD);
    CHECK(elrond::makeDWord(0xABCD, 0x0) == 0xABCD0000);
    CHECK(elrond::makeDWord(0x0, 0x0) == 0x0);
    CHECK(elrond::makeDWord(-1, 0x0) == 0xFFFF0000);
    CHECK(elrond::makeDWord(0x0, -1) == 0xFFFF);
    CHECK(elrond::makeDWord(-1, -1) == 0xFFFFFFFF);

    CHECK(elrond::makeDWord(0x12, 0x34, 0xAB, 0xCD) == 0x1234ABCD);
    CHECK(elrond::makeDWord(0xAB, 0xCD, 0x12, 0x34) == 0xABCD1234);
    CHECK(elrond::makeDWord(0x0, 0x0, 0xAB, 0xCD) == 0xABCD);
    CHECK(elrond::makeDWord(0xAB, 0xCD, 0x0, 0x0) == 0xABCD0000);
    CHECK(elrond::makeDWord(0x0, 0x0, 0x0, 0x0) == 0x0);
    CHECK(elrond::makeDWord(-1, -1, 0x0, 0x0) == 0xFFFF0000);
    CHECK(elrond::makeDWord(0x0, 0x0, -1, -1) == 0xFFFF);
    CHECK(elrond::makeDWord(-1, 0x0, -1, 0x0) == 0xFF00FF00);
    CHECK(elrond::makeDWord(0x0, -1, 0x0, -1) == 0xFF00FF);
    CHECK(elrond::makeDWord(-1, -1, -1, -1) == 0xFFFFFFFF);
}

TEST_CASE("Check highByteOfHighWord() function", "[bitwise]")
{
    CHECK(elrond::highByteHighWord(0x1234ABCD) == 0x12);
    CHECK(elrond::highByteHighWord(0x34ABCD) == 0x0);
    CHECK(elrond::highByteHighWord(0xABCD) == 0x0);
    CHECK(elrond::highByteHighWord(0x0) == 0x0);
    CHECK(elrond::highByteHighWord(-1) == 0xFF);
}

TEST_CASE("Check lowByteOfHighWord() function", "[bitwise]")
{
    CHECK(elrond::lowByteHighWord(0x1234ABCD) == 0x34);
    CHECK(elrond::lowByteHighWord(0x1200ABCD) == 0x0);
    CHECK(elrond::lowByteHighWord(0xABCD) == 0x0);
    CHECK(elrond::lowByteHighWord(0x0) == 0x0);
    CHECK(elrond::lowByteHighWord(-1) == 0xFF);
}

TEST_CASE("Check highByteOfLowWord() function", "[bitwise]")
{
    CHECK(elrond::highByteLowWord(0x1234ABCD) == 0xAB);
    CHECK(elrond::highByteLowWord(0x123400CD) == 0x0);
    CHECK(elrond::highByteLowWord(0x12340000) == 0x0);
    CHECK(elrond::highByteLowWord(0x0) == 0x0);
    CHECK(elrond::highByteLowWord(-1) == 0xFF);
}

TEST_CASE("Check lowByteOfLowWord() function", "[bitwise]")
{
    CHECK(elrond::lowByteLowWord(0x1234ABCD) == 0xCD);
    CHECK(elrond::lowByteLowWord(0x1234AB00) == 0x0);
    CHECK(elrond::lowByteLowWord(0x12340000) == 0x0);
    CHECK(elrond::lowByteLowWord(0x0) == 0x0);
    CHECK(elrond::lowByteLowWord(-1) == 0xFF);
}
