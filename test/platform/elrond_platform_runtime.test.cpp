#include <elrond_mock.hpp>
#include "catch2.hpp"

using namespace elrond::platform;
using elrond::interface::Module;
using elrond::module::BaseGeneric;
using Catch::Matchers::ContainsSubstring;

const std::string TEST_BUILD_DIR = std::string(ELROND_BUILD_DIR) + "/test/";

TEST_CASE("Check elrond::platform::demangle() function", "[platform][demangle]")
{
    CHECK_THAT(demangle<int>(), ContainsSubstring("int"));
    CHECK_THAT(demangle<elrond::string>(), ContainsSubstring("basic_string"));
    CHECK_THAT(demangle<elrond::interface::Module>(), ContainsSubstring("elrond::interface::Module"));
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

TEST_CASE("Check elrond::platform::parseExternalFactoryFromDlHandle() function", "[platform][parseExternalFactoryFromDlHandle]")
{
    DlHandle handle(TEST_BUILD_DIR + "dlobject/ExternalModule");

    try
    {
        auto& factory = parseExternalFactoryFromDlHandle(handle);

        CHECK(factory.apiVersion() == elrond::getApiVersion());
        CHECK(factory.info().name == "External Test Module");
        CHECK(factory.info().author == "Edwino Stein");
        CHECK(factory.info().email== "edwino.stein@gmail.com");
        CHECK(factory.info().version == "1.0.0");

        std::unique_ptr<Module, std::function<void(Module*)>> inst (
            factory.create(),
            [&factory](Module* i){ factory.destroy(i); }
        );
        CHECK(inst != nullptr);
        CHECK(isInstanceOf<BaseGeneric>(inst.get()));
        CHECK(inst->moduleType() == elrond::ModuleType::GENERIC);
    }
    catch(const std::exception&)
    {
        FAIL("Does should not throw an exception");
    }
}
