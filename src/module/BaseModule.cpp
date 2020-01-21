#include "module/BaseModule.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::BaseModule;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;

/*  ****************************************************************************
    **************** elrond::module::BaseModule Implementation *****************
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
