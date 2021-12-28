#include <elrond_mock.hpp>
#include "catch2.hpp"

using elrond::module::BaseGeneric;
using elrond::platform::ModuleInfo;
using elrond::platform::InternalFactoryAdapter;
using Catch::Matchers::Contains;

SCENARIO("Test the module instance factory adapters", "[platform][FactoryAdapter]")
{
    class TestModule : public BaseGeneric {};

    GIVEN("A internal factory adapter to generic module")
    {
        ModuleInfo info = {
            "Test Module",
            "Edwino Stein",
            "edwino.stein@gmail.com",
            "1.0"
        };

        InternalFactoryAdapter<TestModule> adapter(info);

       WHEN("Call the apiVersion getter method")
        {
            const auto apiVer = adapter.apiVersion();
            THEN("Should return the current elrond API version")
            {
                CHECK(apiVer == elrond::getApiVersion());
            }
        }

        WHEN("Call the name getter method")
        {
            auto& name = adapter.name();
            THEN("Should return a string containing the module class name")
            {
                CHECK_THAT(name, Contains("TestModule"));
            }
        }

        WHEN("Call the info getters methods")
        {
            auto& name = adapter.infoName();
            auto& author = adapter.infoAuthor();
            auto& email = adapter.infoEmail();
            auto& verion = adapter.infoVersion();

            THEN("Should return the ModuleInfo values")
            {
                CHECK(name == "Test Module");
                CHECK(author == "Edwino Stein");
                CHECK(email == "edwino.stein@gmail.com");
                CHECK(verion == "1.0");
            }
        }

        WHEN("Call the create method")
        {
            auto inst = adapter.create("test");

            THEN("Should return a Module instance")
            {
                CHECK(inst != nullptr);
                CHECK(inst->name() == "test");
                CHECK(isInstanceOf<BaseGeneric>(inst->instance()));
                CHECK(isInstanceOf<TestModule>(inst->instance()));
                CHECK(inst->instance().moduleType() == elrond::ModuleType::GENERIC);
            }
        }
    }
}
