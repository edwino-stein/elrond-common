#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::module::BaseGeneric;
using elrond::platform::ModuleInfo;
using elrond::interface::Module;
using elrond::platform::Factory;
using Catch::Matchers::ContainsSubstring;

const std::string TEST_BUILD_DIR = std::string(ELROND_BUILD_DIR) + "/test/";

SCENARIO("Test the module instance factory", "[platform][Factory]")
{
    class TestModule : public BaseGeneric {};

    GIVEN("A generic module instance factory")
    {
        ModuleInfo info = {
            "Test Module",
            "Edwino Stein",
            "edwino.stein@gmail.com",
            "1.0"
        };

        Factory<TestModule> factory(info);

        WHEN("Call the apiVersion getter method")
        {
            const auto apiVer = factory.apiVersion();
            THEN("Should return the current elrond API version")
            {
                CHECK(apiVer == elrond::getApiVersion());
            }
        }

        WHEN("Call the info getter method")
        {
            auto& info = factory.info();
            THEN("Should return the ModuleInfo instance")
            {
                CHECK(info.name == "Test Module");
                CHECK(info.author == "Edwino Stein");
                CHECK(info.email == "edwino.stein@gmail.com");
                CHECK(info.version == "1.0");
            }
        }

        WHEN("Call the create and destroy methods")
        {
            std::unique_ptr<Module, std::function<void(Module*)>> inst (
                factory.create(),
                [&factory](Module* i){ factory.destroy(i); }
            );
            
            THEN("Should return a Module instance")
            {
                CHECK(inst != nullptr);
                CHECK(isInstanceOf<BaseGeneric>(inst.get()));
                CHECK(isInstanceOf<TestModule>(inst.get()));
                CHECK(inst->moduleType() == elrond::ModuleType::GENERIC);
            }
        }
    }
}
