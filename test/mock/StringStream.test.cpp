#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::StringStream;

TEST_CASE("[elrond::mock::StringStream] Check integers print")
{
    StringStream ss;

    ss << 123;
    CHECK(ss.getString() == "123");

    ss.flush();
    ss << -123;
    CHECK(ss.getString() == "-123");

    ss.flush();
    ss << static_cast<int>(0xFFFFFFFF);
    CHECK(ss.getString() == "-1");

    ss.flush();
    ss << static_cast<unsigned int>(-1);
    CHECK(ss.getString() == "4294967295");

    ss.flush();
    ss << static_cast<long>(0xFFFFFFFF);
    CHECK(ss.getString() == "4294967295");

    ss.flush();
    ss << static_cast<long>(0xFFFFFFFFFFFFFFFF);
    CHECK(ss.getString() == "-1");

    ss.flush();
    ss << static_cast<unsigned long>(0xFFFFFFFFFFFFFFFF);
    CHECK(ss.getString() == "18446744073709551615");

    ss.flush();
    ss << static_cast<unsigned long>(-1);
    CHECK(ss.getString() == "18446744073709551615");
}

TEST_CASE("[elrond::mock::StringStream] Check double/float print")
{
    StringStream ss;

    ss << 123.456;
    CHECK(ss.getString() == "123.456");

    ss.flush();
    ss << -123.456;
    CHECK(ss.getString() == "-123.456");

    ss.flush();
    ss << static_cast<float>(123.456);
    CHECK(ss.getString() == "123.456");

    ss.flush();
    ss << static_cast<float>(-123.456);
    CHECK(ss.getString() == "-123.456");

    ss.flush();
    ss << 3.14159265359;
    CHECK(ss.getString() == "3.14159");

    ss.flush();
    ss << static_cast<double>(3.14159265359);
    CHECK(ss.getString() == "3.14159");

    ss.flush();
    ss << static_cast<float>(3.14159265359);
    CHECK(ss.getString() == "3.14159");
}

TEST_CASE("[elrond::mock::StringStream] Check char print")
{
    StringStream ss;

    ss << 'a';
    CHECK(ss.getString() == "a");

    ss.flush();
    ss << 'A';
    CHECK(ss.getString() == "A");

    ss.flush();
    ss << static_cast<char>(97);
    CHECK(ss.getString() == "a");

    ss.flush();
    ss << static_cast<char>(127);
    CHECK(ss.getString()[0] == static_cast<char>(127));

    ss.flush();
    ss << static_cast<char>(-1);
    CHECK(ss.getString()[0] == static_cast<char>(-1));

    ss.flush();
    ss << static_cast<unsigned char>(97);
    CHECK(ss.getString() == "a");

    ss.flush();
    ss << static_cast<unsigned char>(255);
    CHECK(static_cast<unsigned char>(ss.getString()[0]) == static_cast<unsigned char>(255));

    ss.flush();
    ss << static_cast<unsigned char>(-1);
    CHECK(static_cast<unsigned char>(ss.getString()[0]) == static_cast<unsigned char>(-1));
}

TEST_CASE("[elrond::mock::StringStream] Check string print")
{
    StringStream ss;

    ss << "Hello world literal";
    CHECK(ss.getString() == "Hello world literal");

    ss.flush();
    const char * strConstChar= "Hello world const char*";
    ss << strConstChar;
    CHECK(ss.getString() == "Hello world const char*");

    ss.flush();
    char strCharArray[] = "Hello world char array";
    ss << strCharArray;
    CHECK(ss.getString() == "Hello world char array");

    ss.flush();
    elrond::string strElrondString = "Hello world elrond string";
    ss << strElrondString;
    CHECK(ss.getString() == "Hello world elrond string");
}

TEST_CASE("[elrond::mock::StringStream] Check concatenation print")
{
    StringStream ss;

    ss << "Hello" << ' ' << "world";
    CHECK(ss.getString() == "Hello world");

    ss.flush();
    ss << "Pi = " << 3.14159265359 << ';';
    CHECK(ss.getString() == "Pi = 3.14159;");

    ss.flush();
    ss << "average = (" << "50" << '+' << 86 << '+' << "37.5" << ")/" << 3;
    CHECK(ss.getString() == "average = (50+86+37.5)/3");
}
