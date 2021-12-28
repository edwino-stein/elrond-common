#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::StringStream;

SCENARIO("Test a mocked StringStream for capture numeric outputs", "[mock][StringStream]")
{
    GIVEN("A StringStram instance")
    {
        StringStream ss;

        WHEN("Capture a positive integer")
        {
            ss << 123;
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "123");
            }
        }

        WHEN("Capture a negative integer")
        {
            ss << -123;
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "-123");
            }
        }

        WHEN("Capture an overflowed integer")
        {
            ss << static_cast<int>(0xFFFFFFFF);
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "-1");
            }
        }

        WHEN("Capture an unsigned integer")
        {
            ss << static_cast<unsigned int>(0xFFFFFFFF);
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "4294967295");
            }
        }

        WHEN("Capture a negative integer as unsigned integer")
        {
            ss << static_cast<unsigned int>(-1);
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "4294967295");
            }
        }

        WHEN("Capture a long")
        {
            ss << static_cast<long>(0xFFFFFFFF);
            THEN("The StringStream must captured the number as string")
            {
                if (sizeof(long) == 4) FAIL();
                if (sizeof(long) == 8) CHECK(ss.getString() == "4294967295");
            }
        }

        WHEN("Capture an overflowed long")
        {
            ss << static_cast<long>(0xFFFFFFFFFFFFFFFF);
            THEN("The StringStream must captured the number as string")
            {
                if (sizeof(long) == 4) FAIL();
                if (sizeof(long) == 8) CHECK(ss.getString() == "-1");
            }
        }

        WHEN("Capture an unsigned long")
        {
            ss << static_cast<unsigned long>(0xFFFFFFFFFFFFFFFF);
            THEN("The StringStream must captured the number as string")
            {
                if (sizeof(unsigned long) == 4) FAIL();
                if (sizeof(unsigned long) == 8) CHECK(ss.getString() == "18446744073709551615");
            }
        }

        WHEN("Capture a negative long as unsigned long")
        {
            ss << static_cast<unsigned long>(-1);
            THEN("The StringStream must captured the number as string")
            {
                if (sizeof(unsigned long) == 4) FAIL();
                if (sizeof(unsigned long) == 8) CHECK(ss.getString() == "18446744073709551615");
            }
        }

        WHEN("Capture a positive double")
        {
            ss << 123.456;
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "123.456");
            }
        }

        WHEN("Capture a negative double")
        {
            ss << -123.456;
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "-123.456");
            }
        }

        WHEN("Capture a positive float")
        {
            ss << static_cast<float>(123.456);
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "123.456");
            }
        }

        WHEN("Capture a negative float")
        {
            ss << static_cast<float>(-123.456);
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "-123.456");
            }
        }

        WHEN("Capture a double with precision loss")
        {
            ss << 3.14159265359;
            THEN("The StringStream must captured the number as string")
            {
                CHECK(ss.getString() == "3.14159");
            }
        }
    }
}

SCENARIO("Test a mocked StringStream for capture string and char outputs", "[mock][StringStream]")
{
    GIVEN("A StringStram instance")
    {
        StringStream ss;

        WHEN("Capture a single printable char")
        {
            ss << 'a';
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(ss.getString() == "a");
            }
        }

        WHEN("Capture a single printable char from your ASCII code")
        {
            ss << static_cast<char>(97);
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(ss.getString() == "a");
            }
        }

        WHEN("Capture a single unprintable char from your ASCII code")
        {
            ss << static_cast<char>(127);
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(ss.getString()[0] == static_cast<char>(127));
            }
        }

        WHEN("Capture a single unprintable char from your ASCII negative code")
        {
            ss << static_cast<char>(-1);
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(ss.getString()[0] == static_cast<char>(-1));
            }
        }

        WHEN("Capture a single printable const char from your ASCII code")
        {
            ss << static_cast<char>(97);
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(ss.getString() == "a");
            }
        }

        WHEN("Capture a single unprintable const char from your ASCII code")
        {
            ss << static_cast<char>(255);
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(
                    static_cast<unsigned char>(ss.getString()[0]) ==
                    static_cast<unsigned char>(255)
                );
            }
        }

        WHEN("Capture a single unprintable const char from your ASCII negative code")
        {
            ss << static_cast<char>(-1);
            THEN("The StringStream must captured the symbol as string")
            {
                CHECK(
                    static_cast<unsigned char>(ss.getString()[0]) ==
                    static_cast<unsigned char>(-1)
                );
            }
        }

        WHEN("Capture a literal string")
        {
            ss << "Hello world literal";
            THEN("The StringStream must captured the string")
            {
                CHECK(ss.getString() == "Hello world literal");
            }
        }

        WHEN("Capture a const char string")
        {
            const char* strConstChar = "Hello world const char";
            ss << strConstChar;
            THEN("The StringStream must captured the string")
            {
                CHECK(ss.getString() == "Hello world const char");
            }
        }

        WHEN("Capture a const char array")
        {
            char strCharArray[] = "Hello world char array";
            ss << strCharArray;
            THEN("The StringStream must captured the string")
            {
                CHECK(ss.getString() == "Hello world char array");
            }
        }

        WHEN("Capture an elrond string")
        {
            elrond::string strElrondString = "Hello world elrond string";
            ss << strElrondString;
            THEN("The StringStream must captured the string")
            {
                CHECK(ss.getString() == "Hello world elrond string");
            }
        }
    }
}

SCENARIO("Test a mocked StringStream for capture concatened outputs", "[mock][StringStream]")
{
    GIVEN("A StringStram instance")
    {
        StringStream ss;

        WHEN("Capture a string and chars")
        {
            ss << "Hello" << ' ' << "world";
            THEN("The StringStream must captured the concated string")
            {
                CHECK(ss.getString() == "Hello world");
            }
        }

        WHEN("Capture a string and numbers")
        {
            ss << "average = (" << "50" << '+' << 86 << '+' << 37.5 << ")/" << 3;
            THEN("The StringStream must captured the concated string")
            {
                CHECK(ss.getString() == "average = (50+86+37.5)/3");
            }
        }
    }
}

SCENARIO("Test a mocked StringStream cleaning buffer", "[mock][StringStream]")
{
    GIVEN("A StringStram instance with something captured")
    {
        StringStream ss;
        ss << "Hello" << ' ' << "world" << ' ' << 123;
        REQUIRE(ss.getString() == "Hello world 123");

        WHEN("Call flush method")
        {
            ss.flush();
            THEN("The captured string must be gone")
            {
                CHECK(ss.getString() == "");
            }
        }
    }
}
