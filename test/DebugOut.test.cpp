#include "elrond-test.hpp"
#include <string>

using elrond::test::DebugOut;

TEST_CASE("DebugOut for Elrond Test Library (int)", "[debug]" )
{

    DebugOut dout(
        [](std::ostringstream& oss)
        {
            REQUIRE(oss.str() == "123");
        }
    );

    dout.put(123);
    dout.put((long) 123);
}

TEST_CASE("DebugOut for Elrond Test Library (double)", "[debug]" )
{

    DebugOut dout(
        [](std::ostringstream& oss)
        {
            REQUIRE(oss.str() == "123.456");
        }
    );

    dout.put(123.456);
}

TEST_CASE("DebugOut for Elrond Test Library (string)", "[debug]" )
{

    DebugOut dout(
        [](std::ostringstream& oss)
        {
            REQUIRE(oss.str() == "hello world");
        }
    );

    dout.put("hello world");

    elrond::String estr = ELROND_STR("hello world");
    dout.put(estr);
}

TEST_CASE("DebugOut for Elrond Test Library (char)", "[debug]" )
{

    DebugOut dout(
        [](std::ostringstream& oss)
        {
            REQUIRE(oss.str() == "c");
        }
    );

    dout.put('c');
}
