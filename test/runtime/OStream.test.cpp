#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::runtime::OStream;

SCENARIO("Test a mocked OStream for capture numeric outputs", "[runtime][OStream]")
{
    GIVEN("A StringStram instance")
    {
        std::ostringstream oss;
        OStream stream(oss);

        WHEN("Capture a positive integer")
        {
            stream << 123;
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "123");
            }
        }

        WHEN("Capture a negative integer")
        {
            stream << -123;
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "-123");
            }
        }

        WHEN("Capture an overflowed integer")
        {
            stream << static_cast<int>(0xFFFFFFFF);
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "-1");
            }
        }

        WHEN("Capture an unsigned integer")
        {
            stream << static_cast<unsigned int>(0xFFFFFFFF);
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "4294967295");
            }
        }

        WHEN("Capture a negative integer as unsigned integer")
        {
            stream << static_cast<unsigned int>(-1);
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "4294967295");
            }
        }

        WHEN("Capture a long")
        {
            stream << static_cast<long>(0xFFFFFFFF);
            THEN("The OStream must captured the number as string")
            {
                if (sizeof(long) == 4) CHECK(oss.str() == "-1");
                if (sizeof(long) == 8) CHECK(oss.str() == "4294967295");
            }
        }

        WHEN("Capture an overflowed long")
        {
            stream << static_cast<long>(0xFFFFFFFFFFFFFFFF);
            THEN("The OStream must captured the number as string")
            {
                if (sizeof(long) == 4) CHECK(oss.str() == "-1");
                if (sizeof(long) == 8) CHECK(oss.str() == "-1");
            }
        }

        WHEN("Capture an unsigned long")
        {
            stream << static_cast<unsigned long>(0xFFFFFFFFFFFFFFFF);
            THEN("The OStream must captured the number as string")
            {
                if (sizeof(unsigned long) == 4) CHECK(oss.str() == "4294967295");
                if (sizeof(unsigned long) == 8) CHECK(oss.str() == "18446744073709551615");
            }
        }

        WHEN("Capture a negative long as unsigned long")
        {
            stream << static_cast<unsigned long>(-1);
            THEN("The OStream must captured the number as string")
            {
                if (sizeof(unsigned long) == 4) CHECK(oss.str() == "4294967295");
                if (sizeof(unsigned long) == 8) CHECK(oss.str() == "18446744073709551615");
            }
        }

        WHEN("Capture a positive double")
        {
            stream << 123.456;
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "123.456");
            }
        }

        WHEN("Capture a negative double")
        {
            stream << -123.456;
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "-123.456");
            }
        }

        WHEN("Capture a positive float")
        {
            stream << static_cast<float>(123.456);
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "123.456");
            }
        }

        WHEN("Capture a negative float")
        {
            stream << static_cast<float>(-123.456);
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "-123.456");
            }
        }

        WHEN("Capture a double with precision loss")
        {
            stream << 3.14159265359;
            THEN("The OStream must captured the number as string")
            {
                CHECK(oss.str() == "3.14159");
            }
        }
    }
}

SCENARIO("Test a mocked OStream for capture string and char outputs", "[runtime][OStream]")
{
    GIVEN("A StringStram instance")
    {
        std::ostringstream oss;
        OStream stream(oss);

        WHEN("Capture a single printable char")
        {
            stream << 'a';
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(oss.str() == "a");
            }
        }

        WHEN("Capture a single printable char from your ASCII code")
        {
            stream << static_cast<char>(97);
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(oss.str() == "a");
            }
        }

        WHEN("Capture a single unprintable char from your ASCII code")
        {
            stream << static_cast<char>(127);
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(oss.str()[0] == static_cast<char>(127));
            }
        }

        WHEN("Capture a single unprintable char from your ASCII negative code")
        {
            stream << static_cast<char>(-1);
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(oss.str()[0] == static_cast<char>(-1));
            }
        }

        WHEN("Capture a single printable const char from your ASCII code")
        {
            stream << static_cast<char>(97);
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(oss.str() == "a");
            }
        }

        WHEN("Capture a single unprintable const char from your ASCII code")
        {
            stream << static_cast<char>(255);
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(
                    static_cast<unsigned char>(oss.str()[0]) ==
                    static_cast<unsigned char>(255)
                );
            }
        }

        WHEN("Capture a single unprintable const char from your ASCII negative code")
        {
            stream << static_cast<char>(-1);
            THEN("The OStream must captured the symbol as string")
            {
                CHECK(
                    static_cast<unsigned char>(oss.str()[0]) ==
                    static_cast<unsigned char>(-1)
                );
            }
        }

        WHEN("Capture a literal string")
        {
            stream << "Hello world literal";
            THEN("The OStream must captured the string")
            {
                CHECK(oss.str() == "Hello world literal");
            }
        }

        WHEN("Capture a const char string")
        {
            const char* strConstChar = "Hello world const char";
            stream << strConstChar;
            THEN("The OStream must captured the string")
            {
                CHECK(oss.str() == "Hello world const char");
            }
        }

        WHEN("Capture a const char array")
        {
            char strCharArray[] = "Hello world char array";
            stream << strCharArray;
            THEN("The OStream must captured the string")
            {
                CHECK(oss.str() == "Hello world char array");
            }
        }

        WHEN("Capture an elrond string")
        {
            elrond::string strElrondString = "Hello world elrond string";
            stream << strElrondString;
            THEN("The OStream must captured the string")
            {
                CHECK(oss.str() == "Hello world elrond string");
            }
        }
    }
}

SCENARIO("Test a mocked OStream for capture concatened outputs", "[runtime][OStream]")
{
    GIVEN("A StringStram instance")
    {
        std::ostringstream oss;
        OStream stream(oss);

        WHEN("Capture a string and chars")
        {
            stream << "Hello" << ' ' << "world";
            THEN("The OStream must captured the concated string")
            {
                CHECK(oss.str() == "Hello world");
            }
        }

        WHEN("Capture a string and numbers")
        {
            stream << "average = (" << "50" << '+' << 86 << '+' << 37.5 << ")/" << 3;
            THEN("The OStream must captured the concated string")
            {
                CHECK(oss.str() == "average = (50+86+37.5)/3");
            }
        }
    }
}
