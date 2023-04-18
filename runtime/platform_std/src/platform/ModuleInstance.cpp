#include "platform/ModuleInstance.hpp"

using elrond::platform::ModuleInstance;
using elrond::platform::FactoryInterface;
using elrond::interface::Module;

ModuleInstance::ModuleInstance(const elrond::string& name, const FactoryInterface& factory)
:
    _name(name),
    _instance(
        factory.create(),
        [&factory](Module* inst) {
            factory.destroy(inst);
        }
    )
{}

ModuleInstance::~ModuleInstance() {}

Module& ModuleInstance::instance() const
{
    return *(this->_instance.get());
}

const elrond::string& ModuleInstance::name() const
{
    return this->_name;
}
