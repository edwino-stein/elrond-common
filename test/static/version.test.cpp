#include <elrond.hpp>
#include "catch2.hpp"

TEST_CASE("Check version decoding dword", "[version]")
{
    auto version = elrond::getApiVersion();
    CHECK(elrond::BUILD_TYPE == elrond::highByteHighWord(version));
    CHECK(elrond::MAJOR_VER == elrond::lowByteHighWord(version));
    CHECK(elrond::MINOR_VER == elrond::highByteLowWord(version));
    CHECK(elrond::PATCH_VER == elrond::lowByteLowWord(version));
}

TEST_CASE("Check build type decoding byte", "[version]")
{
    auto buildType = elrond::highByteHighWord(elrond::getApiVersion());
    CHECK(elrond::BUILD_TYPE == buildType);
    CHECK(ELROND_BUILD_TYPE == (buildType & 0xF0));
    CHECK(ELROND_API_DEV_STAGE == (buildType & 0x0F));
}
