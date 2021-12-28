#include <elrond_mock.hpp>
#include "catch2.hpp"

using namespace elrond::platform;
using Catch::Matchers::Contains;

TEST_CASE("Check elrond::platform::demangle() function", "[platform][demangle]")
{
    CHECK_THAT(demangle<int>(), Contains("int"));
    CHECK_THAT(demangle<elrond::string>(), Contains("std::basic_string"));
    CHECK_THAT(demangle<elrond::interface::Module>(), Contains("elrond::interface::Module"));
}

TEST_CASE("Check elrond::platform::isAbsolutePath() function", "[platform][isAbsolutePath]")
{
    CHECK(isAbsolutePath("/home/user/file.txt"));
    CHECK(!isAbsolutePath("./file.txt"));
    CHECK(!isAbsolutePath("../user/file.txt"));

    CHECK(isAbsolutePath("c:\\home\\user\\file.txt"));
    CHECK(isAbsolutePath("\\home\\user\\file.txt"));
    CHECK(!isAbsolutePath(".\\file.txt"));
    CHECK(!isAbsolutePath("..\\user\\file.txt"));

    CHECK(!isAbsolutePath("file.txt"));
}

TEST_CASE("Check elrond::platform::fileExtension() function", "[platform][fileExtension]")
{
    CHECK(fileExtension("/home/user/file.txt") == ".txt");
    CHECK(fileExtension("./file") == "");
    CHECK(fileExtension("../file") == "");
    CHECK(fileExtension("./file.txt") == ".txt");
    CHECK(fileExtension("../user/file.txt") == ".txt");

    CHECK(fileExtension("\\home\\user\\file.txt") == ".txt");
    CHECK(fileExtension("c:\\home\\user\\file.txt") == ".txt");
    CHECK(fileExtension(".\\file") == "");
    CHECK(fileExtension("..\\file") == "");
    CHECK(fileExtension(".\\file.txt") == ".txt");
    CHECK(fileExtension("..\\user\\file.txt") == ".txt");

    CHECK(fileExtension("file.txt") == ".txt");
    CHECK(fileExtension("file.subext.txt") == ".txt");
    CHECK(fileExtension(".txt") == ".txt");
    CHECK(fileExtension("file") == "");
}

TEST_CASE("Check elrond::platform::normilizePath() function", "[platform][normilizePath]")
{
    #ifdef ELROND_WINDOWS_PLATFORM
        CHECK(normilizePath("C:\\home\\user\\file.txt") == "C:\\home\\user\\file.txt");
        CHECK(normilizePath("\\home\\user\\file.txt") == "\\home\\user\\file.txt");
        CHECK(normilizePath(".\\file.txt") == ".\\file.txt");
        CHECK(normilizePath("..\\user\\file.txt") == "..\\user\\file.txt");

        CHECK(normilizePath("/home/user/file.txt") == "\\home\\user\\file.txt");
        CHECK(normilizePath("./file.txt") == ".\\file.txt");
        CHECK(normilizePath("../user/file.txt") == "..\\user\\file.txt");
    #else
        CHECK(normilizePath("/home/user/file.txt") == "/home/user/file.txt");
        CHECK(normilizePath("./file.txt") == "./file.txt");
        CHECK(normilizePath("../user/file.txt") == "../user/file.txt");

        CHECK(normilizePath("C:\\home\\user\\file.txt") == "/home/user/file.txt");
        CHECK(normilizePath("\\home\\user\\file.txt") == "/home/user/file.txt");
        CHECK(normilizePath(".\\file.txt") == "./file.txt");
        CHECK(normilizePath("..\\user\\file.txt") == "../user/file.txt");
    #endif

    CHECK(normilizePath("file.txt") == "file.txt");
    CHECK(normilizePath("file") == "file");
}
