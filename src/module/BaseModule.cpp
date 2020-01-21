#include "module/BaseModule.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::BaseModule;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::LoopControl;

/*  ****************************************************************************
    **************** elrond::module::BaseModule Implementation *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseModule::~BaseModule(){}
#endif

void BaseModule::onInit(ConfigMap& cfg, LoopControl& lc){}
void BaseModule::onStart(){}
void BaseModule::loop(){}
void BaseModule::onStop(){}

elrond::ModuleType BaseModule::getType() const
{
    return elrond::ModuleType::GENERIC;
}
