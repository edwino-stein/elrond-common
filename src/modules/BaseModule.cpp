#include "modules/BaseModule.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "interfaces/ConfigMapInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ConfigMapInterface;

/*  ****************************************************************************
    ************** Implementation for elrond::modules::BaseModule **************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseModule::~BaseModule(){}
#endif

void BaseModule::onInit(ConfigMapInterface &cfg){}
void BaseModule::onStart(){}
void BaseModule::loop(){}
void BaseModule::onStop(){}

elrond::ModuleType BaseModule::getType() const {
    return elrond::ModuleType::GENERIC;
}

elrond::ModuleLoopControl &BaseModule::getLoopControl(){
    return this->_loopControl;
}
