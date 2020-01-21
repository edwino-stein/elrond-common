#include "modules/BaseModule.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using namespace elrond::modules;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;

/*  ****************************************************************************
    **************** elrond::modules::BaseModule Implementation ****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseModule::~BaseModule(){}
#endif

void BaseModule::onInit(ConfigMap& cfg){}
void BaseModule::onStart(){}
void BaseModule::loop(){}
void BaseModule::onStop(){}

elrond::ModuleType BaseModule::getType() const
{
    return elrond::ModuleType::GENERIC;
}

elrond::ModuleLoopControl &BaseModule::getLoopControl()
{
    return this->_loopControl;
}
