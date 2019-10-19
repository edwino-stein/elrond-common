#include "modules/ExampleModule.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "runtime/config/ConfigMap.hpp"
#include "interfaces/DebugOutInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;

/*  ****************************************************************************
    ************ Implementation for elrond::modules::ExampleModule *************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    ExampleModule::~ExampleModule(){}
#endif

void ExampleModule::onInit(ConfigMap &cfg) {
    elrond::dout().putLn("ExampleModule::onInit");

    this->getLoopControl().time = 100;
    if(cfg.isBool("allowLoop")) this->getLoopControl().allow = cfg.asBool("allowLoop");
    if(cfg.isBool("asyncLoop")) this->getLoopControl().async = cfg.asBool("asyncLoop");
    if(cfg.isInt("timeLoop")) this->getLoopControl().time = cfg.asInt("timeLoop");
}

void ExampleModule::onStart() {
    elrond::dout().putLn("ExampleModule::onStart");
}

void ExampleModule::loop() {
    elrond::dout().put("ExampleModule::loop");
    if(this->getLoopControl().async) elrond::dout().putLn(" (async)");
    else elrond::dout().putLn(" (sync)");
}

void ExampleModule::onStop() {
    elrond::dout().putLn("ExampleModule::onStop");
}

const char *ExampleModule::_getInternalName(){
    return "elrond::ExampleModule";
}

const char *ExampleModule::_infoMainClassName(){
    return "ExampleModule";
}

int ExampleModule::_infoApiVersion(){
    return ELROND_API_VERSION;
}

int ExampleModule::_infoApiRevision(){
    return ELROND_API_REVISION;
}

const char *ExampleModule::_infoPrettyName(){
    return "Example Module";
}

const char *ExampleModule::_infoAuthorName(){
    return "Edwino Stein";
}

const char *ExampleModule::_infoAuthorEmail(){
    return "edwino.stein@gmail.com";
}

const char *ExampleModule::_infoVersion(){
    return "1.0";
}
