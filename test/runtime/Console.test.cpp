#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::runtime::Console;
using elrond::mock::ConsoleAdapter;

SCENARIO("Test a mocked console instance for info outputs", "[runtime][Console]")
{
    GIVEN("A Console mocked with and ConsoleAdapter setted to handle info outputs")
    {
        std::ostringstream oss;
        ConsoleAdapter adapter([&oss](std::ostringstream& msg) { oss << msg.str(); });
        Console console("TEST", adapter);

        WHEN("Calls info method passing a single char")
        {
            console.info('a');
            THEN("The stream must capture the same single char")
            {
                CHECK(oss.str() == "a");
            }
        }

        WHEN("Calls info method passing a single unsigned char")
        {
            console.info(static_cast<unsigned char>(255));
            THEN("The stream must capture the same single unsigned char")
            {
                CHECK(
                    static_cast<unsigned char>(oss.str()[0]) ==
                    static_cast<unsigned char>(255)
                );
            }
        }

        WHEN("Calls info method passing a literal string")
        {
            console.info("Hello World literal"); 
            THEN("The stream must capture the same literal string")
            {
                CHECK(oss.str() == "Hello World literal");
            }
        }

        WHEN("Calls info method passing a const char* string")
        {
            const char* strConstChar = "Hello world const char*";
            console.info(strConstChar);
            THEN("The stream must capture the same const char* string")
            {
                CHECK(oss.str() == "Hello world const char*");
            }
        }

        WHEN("Calls info method passing an elrond string")
        {
            elrond::string strElrondString = "Hello world elrond string";
            console.info(strElrondString);
            THEN("The stream must capture the same elrond string")
            {
                CHECK(oss.str() == "Hello world elrond string");
            }
        }

        WHEN("Calls info method passing an integer")
        {
            console.info(123);
            THEN("The stream must capture the integer as string")
            {
                CHECK(oss.str() == "123");
            }
        }

        WHEN("Calls info method passing an unsigned integer")
        {
            console.info(static_cast<unsigned int>(-1));
            THEN("The stream must capture the unsigned integer as string")
            {
                CHECK(oss.str() == "4294967295");
            }
        }

        WHEN("Calls info method passing a long")
        {
            console.info(static_cast<long>(0xFFFFFFFFFFFFFFFF));
            THEN("The stream must capture the long as string")
            {
                if (sizeof(long) == 4) CHECK(oss.str() == "-1");
                if (sizeof(long) == 8) CHECK(oss.str() == "-1");
            }
        }

        WHEN("Calls info method passing an unsigned long")
        {
            console.info(static_cast<unsigned long>(0xFFFFFFFFFFFFFFFF));
            THEN("The stream must capture the unsigned long as string")
            {
                if (sizeof(unsigned long) == 4) CHECK(oss.str() == "4294967295");
                if (sizeof(unsigned long) == 8) CHECK(oss.str() == "18446744073709551615");
            }
        }

        WHEN("Calls info method passing a double")
        {
            console.info(3.14159265359);
            THEN("The stream must capture the double as string")
            {
                CHECK(oss.str() == "3.14159");
            }
        }

        WHEN("Calls info method passing a float")
        {
            console.info(static_cast<float>(3.14159265359));
            THEN("The stream must capture the float as string")
            {
                CHECK(oss.str() == "3.14159");
            }
        }

        WHEN("Calls info method passing a lambda function")
        {
            elrond::string str = "Hello World";
            console.info(
                [&str](elrond::Stream& s)
                {
                    s << "Message" << ':' << str << "!!!\n";
                    s << "Integer:" << 123 << '\n';
                    s << "Double:" << 3.14159265359 << '\n';
                }
            );

            THEN("The stream must capture everything as string")
            {
                CHECK(
                    oss.str() ==
                    "Message:Hello World!!!\nInteger:123\nDouble:3.14159\n"
                );
            }
        }
    }
}

SCENARIO("Test a mocked console instance for error outputs", "[runtime][Console]")
{
    GIVEN("A Console mocked with and ConsoleAdapter setted to handle error outputs")
    {
        std::ostringstream oss;
        ConsoleAdapter adapter(
            [](std::ostringstream&) {},
            [&oss](std::ostringstream& msg) { oss << msg.str(); }
        );

        Console console("TEST", adapter);

        WHEN("Calls error method passing a literal string")
        {
            console.error("This is an error literal"); 
            THEN("The stream must capture the same literal string")
            {
                CHECK(oss.str() == "This is an error literal");
            }
        }

        WHEN("Calls error method passing a const char* string")
        {
            const char* strConstChar = "This is an error const char*";
            console.error(strConstChar);
            THEN("The stream must capture the same const char* string")
            {
                CHECK(oss.str() == "This is an error const char*");
            }
        }

        WHEN("Calls error method passing an elrond string")
        {
            elrond::string strElrondString = "This is an error elrond string";
            console.error(strElrondString);
            THEN("The stream must capture the same elrond string")
            {
                CHECK(oss.str() == "This is an error elrond string");
            }
        }

        WHEN("Calls error method passing a lambda function")
        {
            elrond::string str = "Error Messagem";
            console.error(
                [&str](elrond::Stream& s)
                {
                    s << "Error" << ':' << str << '\n';
                    s << "Code:" << 5 << '\n';
                }
            );

            THEN("The stream must capture everything as string")
            {
                CHECK(
                    oss.str() ==
                    "Error:Error Messagem\nCode:5\n"
                );
            }
        }
    }
}
