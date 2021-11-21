#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::Console;
using elrond::mock::StringStream;
using elrond::interface::Stream;

SCENARIO("Test a mocked console instance for info outputs", "[mock][Console]")
{
    GIVEN("A Console and StringStram instance setted to handle info outputs")
    {
        StringStream ss;
        Console console([&ss](const elrond::StreamH& h) { h(ss); });

        WHEN("Calls info method passing a single char")
        {
            console.info('a');
            THEN("The StringStream must capture the same single char")
            {
                CHECK(ss.getString() == "a");
            }
        }

        WHEN("Calls info method passing a single unsigned char")
        {
            console.info(static_cast<unsigned char>(255));
            THEN("The StringStream must capture the same single unsigned char")
            {
                CHECK(
                    static_cast<unsigned char>(ss.getString()[0]) ==
                    static_cast<unsigned char>(255)
                );
            }
        }

        WHEN("Calls info method passing a literal string")
        {
            console.info("Hello World literal"); 
            THEN("The StringStream must capture the same literal string")
            {
                CHECK(ss.getString() == "Hello World literal");
            }
        }

        WHEN("Calls info method passing a const char* string")
        {
            const char* strConstChar = "Hello world const char*";
            console.info(strConstChar);
            THEN("The StringStream must capture the same const char* string")
            {
                CHECK(ss.getString() == "Hello world const char*");
            }
        }

        WHEN("Calls info method passing an elrond string")
        {
            elrond::string strElrondString = "Hello world elrond string";
            console.info(strElrondString);
            THEN("The StringStream must capture the same elrond string")
            {
                CHECK(ss.getString() == "Hello world elrond string");
            }
        }

        WHEN("Calls info method passing an integer")
        {
            console.info(123);
            THEN("The StringStream must capture the integer as string")
            {
                CHECK(ss.getString() == "123");
            }
        }

        WHEN("Calls info method passing an unsigned integer")
        {
            console.info(static_cast<unsigned int>(-1));
            THEN("The StringStream must capture the unsigned integer as string")
            {
                CHECK(ss.getString() == "4294967295");
            }
        }

        WHEN("Calls info method passing a long")
        {
            console.info(static_cast<long>(0xFFFFFFFFFFFFFFFF));
            THEN("The StringStream must capture the long as string")
            {
                CHECK(ss.getString() == "-1");
            }
        }

        WHEN("Calls info method passing an unsigned long")
        {
            console.info(static_cast<unsigned long>(0xFFFFFFFFFFFFFFFF));
            THEN("The StringStream must capture the unsigned long as string")
            {
                CHECK(ss.getString() == "18446744073709551615");
            }
        }

        WHEN("Calls info method passing a double")
        {
            console.info(3.14159265359);
            THEN("The StringStream must capture the double as string")
            {
                CHECK(ss.getString() == "3.14159");
            }
        }

        WHEN("Calls info method passing a float")
        {
            console.info(static_cast<float>(3.14159265359));
            THEN("The StringStream must capture the float as string")
            {
                CHECK(ss.getString() == "3.14159");
            }
        }

        WHEN("Calls info method passing a lambda function")
        {
            elrond::string str = "Hello World";
            console.info(
                [&str](Stream& s)
                {
                    s << "Message" << ':' << str << "!!!\n";
                    s << "Integer:" << 123 << '\n';
                    s << "Double:" << 3.14159265359 << '\n';
                }
            );

            THEN("The StringStream must capture everything as string")
            {
                CHECK(
                    ss.getString() ==
                    "Message:Hello World!!!\nInteger:123\nDouble:3.14159\n"
                );
            }
        }
    }
}
