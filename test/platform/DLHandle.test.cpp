#include <platform/DlHandle.ipp>
#include "catch2.hpp"

using elrond::platform::DlHandle;
using Catch::Matchers::Contains;
using Catch::Matchers::StartsWith;
using Catch::Matchers::EndsWith;

SCENARIO("Test Dynamic Load Handle generic interface", "[platform][DLHandle]")
{
    GIVEN("An object loaded with the DLHandle class")
    {
        DlHandle object("./dlobject/dlobject");

        WHEN("Get a pointer to function void concat(std::string&, const std::string&)")
        {
            auto concat = object.getFunction<void, std::string&, const std::string&>("concat");

            THEN("Must returns a non null pointer to function concat()")
            {
                REQUIRE(concat != nullptr);
            }

            WHEN("Call the function concat()")
            {
                std::string msg = "Message: ";
                concat(msg, "Hello world");
                THEN("The function concat() must concatenate two strings")
                {
                    CHECK(msg == "Message: Hello world");
                }
            }
        }

        WHEN("Get a pointer to function unsigned int getRandom(const unsigned int, const unsigned int)")
        {
            auto getRandom = object.getFunction<unsigned int, const unsigned int, const unsigned int>("getRandom");

            THEN("Must returns a non null pointer to function getRandom()")
            {
                REQUIRE(getRandom != nullptr);
            }

            WHEN("Call the function getRandom()")
            {
                const auto num = getRandom(1, 10);
                THEN("The function getRandom() must return a random number between 1 and 10")
                {
                    CHECK(num >= 1);
                    CHECK(num <= 10);
                }
            }
        }

        WHEN("Get a pointer to function defined function but with a wrong pointer type")
        {
            try
            {
                auto concat = object.getFunction<int>("concat");
                THEN("Shold return a valid pointer but wrong type")
                {
                    REQUIRE(concat != nullptr);
                    REQUIRE(concat.target<int(*)()>());
                    REQUIRE(concat.target<void(*)(std::string&, const std::string&)>() == nullptr);
                }
            }
            catch(const std::exception& e)
            {
                FAIL("Not should throw an exception"); 
            }
        }

        WHEN("Get a pointer to function undefined function")
        {
            try
            {
                auto undefined = object.getFunction<void>("undefined");
                FAIL("Must throw an exception"); 
            }
            catch(const std::exception& e)
            {
                THEN("Should throw an exception")
                {
                    REQUIRE(e.what() != nullptr);
                    REQUIRE(std::string(e.what()) != "");
                }
            }
        }
    }
}

TEST_CASE("Try to instantiate a instance of DlHandle with invalid object path", "[platform][DLHandle]")
{
    REQUIRE_THROWS([](){
        DlHandle object("dlobject_wrong");
    }());
}

TEST_CASE("Check static DlHandle::parseObjectPath() method", "[platform][DLHandle]")
{
    CHECK_THAT(
        DlHandle::parseObjectPath("dlobject"),
        StartsWith("./dlobject") || StartsWith(".\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("./dlobject"),
        StartsWith("./dlobject") || StartsWith(".\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("./dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("../dlobject"),
        StartsWith("../dlobject") || StartsWith("..\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("../dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath(".\\dlobject"),
        StartsWith("./dlobject") || StartsWith(".\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath(".\\dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("..\\dlobject"),
        StartsWith("../dlobject") || StartsWith("..\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("..\\dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("/dlobject"),
        StartsWith("/dlobject") || StartsWith("\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("/dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("c:\\dlobject"),
        StartsWith("/dlobject") || StartsWith("c:\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("c:\\dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("\\dlobject"),
        StartsWith("/dlobject") || StartsWith("\\dlobject")
    );

    CHECK_THAT(
        DlHandle::parseObjectPath("\\dlobject"),
        EndsWith(".dylib") || EndsWith(".so") || EndsWith(".dll")
    );
}
