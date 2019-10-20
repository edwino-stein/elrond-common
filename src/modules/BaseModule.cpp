#include "modules/BaseModule.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "runtime/config/ConfigMap.hpp"

using namespace elrond::modules;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;

/*  ****************************************************************************
    ************** Implementation for elrond::modules::BaseModule **************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    BaseModule::~BaseModule(){}
#endif

void BaseModule::onInit(ConfigMap &cfg){}
void BaseModule::onStart(){}
void BaseModule::loop(){}
void BaseModule::onStop(){}

elrond::ModuleType BaseModule::getType() const {
    return elrond::ModuleType::GENERIC;
}

elrond::ModuleLoopControl &BaseModule::getLoopControl(){
    return this->_loopControl;
}
