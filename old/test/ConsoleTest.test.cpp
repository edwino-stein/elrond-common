#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::ConsoleTest;

TEST_CASE("[elrond::test::ConsoleTest] Integers print test")
{
    EXPECT_ASSERTS(4);

    ConsoleTest console(
        [](std::ostringstream& oss)
        { CHECK_N_COUNT(oss.str() == "123"); },
        false
    );

    console << (int) 123 << elrond::endl;
    console << (unsigned int) 123 << elrond::endl;
    console << (long) 123 << elrond::endl;
    console << (unsigned long) 123 << elrond::endl;

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::ConsoleTest] Double print test")
{
    EXPECT_ASSERTS(1);

    ConsoleTest console(
        [](std::ostringstream& oss)
        { CHECK_N_COUNT(oss.str() == "123.456"); },
        false
    );

    console << 123.456 << elrond::endl;

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::ConsoleTest] Strings print test")
{
    EXPECT_ASSERTS(2);

    ConsoleTest console(
        [](std::ostringstream& oss)
        { CHECK_N_COUNT(oss.str() == "hello world"); },
        false
    );

    console << "hello world" << elrond::endl;

    elrond::String str = "hello world";
    console << str << elrond::endl;

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::ConsoleTest] Char print test")
{
    EXPECT_ASSERTS(1);

    ConsoleTest console(
        [](std::ostringstream& oss)
        { CHECK_N_COUNT(oss.str() == "c"); },
        false
    );

    console << 'c' << elrond::endl;

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::ConsoleTest] Unsigned char print test")
{
    EXPECT_ASSERTS(1);

    ConsoleTest console(
        [](std::ostringstream& oss)
        { CHECK_N_COUNT((unsigned char) oss.str()[0] == 234); },
        false
    );

    console << (unsigned char) 234 << elrond::endl;

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::ConsoleTest] Complex print test")
{
    EXPECT_ASSERTS(1);

    ConsoleTest console(
        [](std::ostringstream& oss)
        {
            elrond::String expected = "Elrond Common Library v";
            expected += std::to_string(ELROND_API_MAJOR) + ".";
            expected += std::to_string(ELROND_API_MINOR) + ".";
            expected += std::to_string(ELROND_API_PATCH) + "-";
            expected += ELROND_TO_STR(ELROND_DEV_STAGE_NAME);

            CHECK_N_COUNT(oss.str() == expected);
        },
        false
    );

    console << "Elrond Common Library v";
    console << ELROND_API_MAJOR << '.';
    console << ELROND_API_MINOR << '.';
    console << ELROND_API_PATCH << '-';
    console << ELROND_TO_STR(ELROND_DEV_STAGE_NAME) << elrond::endl;

    REQUIRE_ALL_DONE("Check if all tests are done");
}
