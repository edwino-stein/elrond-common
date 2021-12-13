#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::module::BaseGeneric;
using elrond::platform::ModuleInfo;
using elrond::interface::Module;
using elrond::platform::Factory;
using elrond::platform::ModuleInstanceH;
using Catch::Matchers::Contains;

SCENARIO("Test the module instance factories", "[platform][Factory]")
{
    class TestModule : public BaseGeneric {};

    GIVEN("A generic module instance factory")
    {
        ModuleInfo info = {
            .name = "Test Module",
            .author = "Edwino Stein",
            .email = "edwino.stein@gmail.com",
            .version = "1.0"
        };

        Factory<TestModule> factory(info, "TestModule>");

        WHEN("Call the apiVersion getter method")
        {
            const auto apiVer = factory.apiVersion();
            THEN("Should return the current elrond API version")
            {
                CHECK(apiVer == elrond::getApiVersion());
            }
        }

        WHEN("Call the name getter method")
        {
            auto& name = factory.name();
            THEN("Should return a string containing the module class name")
            {
                CHECK_THAT(name, Contains("TestModule"));
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
            ModuleInstanceH inst(factory.create(), [&factory](Module* p) { factory.destroy(p); });
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
