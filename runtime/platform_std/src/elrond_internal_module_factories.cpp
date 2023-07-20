#include <elrond_platform_runtime_types.hpp>
#include "module/HelloWorld.hpp"

using elrond::platform::ModuleInfo;
using elrond::platform::Factory;
using IFactory = elrond::interface::Factory;

template<class M>
inline IFactory* makeInternalModuleFactory(const ModuleInfo& info)
{
    static Factory<M> factoryInstance(info);
    return &factoryInstance;
}

std::map<std::string, IFactory*>& elrond::platform::internalModuleFactories()
{
    static std::map<std::string, IFactory*> factories = {
        std::make_pair(
            "elrond::HelloWorld", makeInternalModuleFactory<elrond::module::HelloWorld>(
            {"Hello World", "Edwino Stein", "edwino.stein@gmail.com", "1.0.0"})
        )
    };

    return factories;
}
