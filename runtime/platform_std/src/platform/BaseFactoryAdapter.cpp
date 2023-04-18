#include "platform/BaseFactoryAdapter.hpp"
#include "platform/ModuleInstance.hpp"

using elrond::platform::BaseFactoryAdapter;
using elrond::platform::ModuleInstance;
using elrond::platform::ModuleInstanceP;

const std::string& BaseFactoryAdapter::name() const
{
    return this->factory().name();
}

elrond::dWord BaseFactoryAdapter::apiVersion() const
{
    return this->factory().apiVersion();
}

const std::string& BaseFactoryAdapter::infoName() const
{
    if (this->factory().info().name == "") return this->name();
    return  this->factory().info().name;
}

const std::string& BaseFactoryAdapter::infoAuthor() const
{
    return this->factory().info().author;
}

const std::string& BaseFactoryAdapter::infoEmail() const
{
    return this->factory().info().email;
}

const std::string& BaseFactoryAdapter::infoVersion() const
{
    return this->factory().info().version;
}

ModuleInstanceP BaseFactoryAdapter::create(const std::string& name) const
{
    return std::make_shared<ModuleInstance>(name, this->factory());
}
