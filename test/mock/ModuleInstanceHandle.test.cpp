#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::mock::InternalInstanceModuleHandle;
using elrond::mock::ExternalInstanceModuleHandle;
using elrond::module::BaseGeneric;
using elrond::platform::ModuleInfo;
using Catch::Matchers::ContainsSubstring;

const std::string TEST_BUILD_DIR = std::string(ELROND_BUILD_DIR) + "/test/";
class TestModule : public BaseGeneric {};

SCENARIO("Test mocked module instance handles", "[mock][ModuleInstanceHandle]")
{
    GIVEN("A internal module instance handle to generic module with a custom module info")
    {
        InternalInstanceModuleHandle<TestModule> handle (
            "test",
            {
                "Test Module",
                "Edwino Stein",
                "edwino.stein@gmail.com",
                "1.0"
            }
        );

        WHEN("Call factory getter")
        {
            auto& factory = handle.factory();
            THEN("Should return the a factory of TestModule")
            {
                CHECK(isInstanceOf<elrond::platform::Factory<TestModule>>(factory));
            }

            AND_THEN("The API version should be the expected")
            {
                CHECK(factory.apiVersion() == elrond::getApiVersion());
            }

            AND_THEN("The module info should be the same as passed to constructor")
            {
                CHECK(factory.info().name == "Test Module");
                CHECK(factory.info().author == "Edwino Stein");
                CHECK(factory.info().email == "edwino.stein@gmail.com");
                CHECK(factory.info().version == "1.0");
            }
        }

        WHEN("Call the name getter")
        {
            auto name = handle.name();

            THEN("Should return a Module instance")
            {
                CHECK(name == "test");
            }
        }

        WHEN("Call the instance getter")
        {
            auto& inst = handle.instance();

            THEN("Should return a TestModule instance")
            {
                CHECK(isInstanceOf<TestModule>(inst));
            }
        }
    }

    GIVEN("A external module instance handle")
    {
        ExternalInstanceModuleHandle handle ("test", TEST_BUILD_DIR + "dlobject/ExternalModule");

        WHEN("Call factory getter")
        {
            auto& factory = handle.factory();

            THEN("The API version should be the expected")
            {
                CHECK(factory.apiVersion() == elrond::getApiVersion());
            }

            AND_THEN("The module info should be the expected")
            {
                CHECK(factory.info().name == "External Test Module");
                CHECK(factory.info().author == "Edwino Stein");
                CHECK(factory.info().email== "edwino.stein@gmail.com");
                CHECK(factory.info().version == "1.0.0");
            }
        }

        WHEN("Call the name getter")
        {
            auto name = handle.name();

            THEN("Should return a Module instance")
            {
                CHECK(name == "test");
            }
        }

        WHEN("Call the instance getter")
        {
            auto& inst = handle.instance();

            THEN("Should return a TestModule instance")
            {
                CHECK(isInstanceOf<elrond::module::BaseGeneric>(inst));
            }
        }
    }
}
