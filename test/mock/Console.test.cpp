#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::Console;
using elrond::mock::StringStream;
using elrond::interface::Stream;

TEST_CASE("[elrond::mock::Console] Check stream handle info")
{
    StringStream ss;

    Console console(
        [&ss](const elrond::StreamH& handle)
        {
            ss.flush();
            handle(ss);
        }
    );

    console.info([](Stream& s) { s << "Hello world"; });
    CHECK(ss.getString() == "Hello world");

    console.info([](Stream& s) { s << 123; });
    CHECK(ss.getString() == "123");

    console.info([](Stream& s) { s << 3.14; });
    CHECK(ss.getString() == "3.14");

    elrond::string str = "Hello World";
    console.info([&str](Stream& s) { s << "Message" << ':' << str << "!!!"; });
    CHECK(ss.getString() == "Message:Hello World!!!");
}

TEST_CASE("[elrond::mock::Console] Check info prints")
{
    StringStream ss;

    Console console(
        [&ss](const elrond::StreamH& handle)
        {
            ss.flush();
            handle(ss);
        }
    );

    console.info(123);
    CHECK(ss.getString() == "123");

    console.info(static_cast<unsigned int>(-1));
    CHECK(ss.getString() == "4294967295");

    console.info(static_cast<long>(0xFFFFFFFFFFFFFFFF));
    CHECK(ss.getString() == "-1");

    console.info(static_cast<unsigned long>(0xFFFFFFFFFFFFFFFF));
    CHECK(ss.getString() == "18446744073709551615");

    console.info(3.14159265359);
    CHECK(ss.getString() == "3.14159");

    console.info(static_cast<float>(3.14159265359));
    CHECK(ss.getString() == "3.14159");

    console.info('a');
    CHECK(ss.getString() == "a");

    console.info(static_cast<unsigned char>(255));
    CHECK(static_cast<unsigned char>(ss.getString()[0]) == static_cast<unsigned char>(255));

    console.info("Hello World literal");
    CHECK(ss.getString() == "Hello World literal");

    const char* strConstChar = "Hello world const char*";
    console.info(strConstChar);
    CHECK(ss.getString() == "Hello world const char*");


    char strCharArray[] = "Hello world char array";
    console.info(strCharArray);
    CHECK(ss.getString() == "Hello world char array");

    elrond::string strElrondString = "Hello world elrond string";
    console.info(strElrondString);
    CHECK(ss.getString() == "Hello world elrond string");
}
