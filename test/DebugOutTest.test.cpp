#include "elrond-catch.hpp"
#include "elrond_test.hpp"

using elrond::test::DebugOutTest;

TEST_CASE("DebugOutTest for Elrond Test Library (int)", "[debug]" )
{
    EXPECT_ASSERTS(2);

    DebugOutTest dout(
        [](std::ostringstream& oss)
        {
            CHECK_N_COUNT(oss.str() == "123");
        }
    );

    dout.put(123);
    dout.put((long) 123);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("DebugOutTest for Elrond Test Library (double)", "[debug]" )
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout(
        [](std::ostringstream& oss)
        {
            CHECK_N_COUNT(oss.str() == "123.456");
        }
    );

    dout.put(123.456);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("DebugOutTest for Elrond Test Library (string)", "[debug]" )
{
    EXPECT_ASSERTS(2);

    DebugOutTest dout(
        [](std::ostringstream& oss)
        {
            CHECK_N_COUNT(oss.str() == "hello world");
        }
    );

    dout.put("hello world");

    elrond::String estr = ELROND_STR("hello world");
    dout.put(estr);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("DebugOutTest for Elrond Test Library (char)", "[debug]" )
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout(
        [](std::ostringstream& oss)
        {
            CHECK_N_COUNT(oss.str() == "c");
        }
    );

    dout.put('c');

    REQUIRE_ALL_DONE("Check if all tests are done");
}
