#include "modules/Example.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "runtime/config/ConfigMap.hpp"
#include "interfaces/ConfigMapInterface.hpp"
#include "interfaces/DebugOutInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;
using elrond::interfaces::ConfigMapInterface;

/*  ****************************************************************************
    *************** Implementation for elrond::modules::Example ****************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    Example::~Example(){}
#endif

void Example::onInit(ConfigMapInterface &cfg) {
    elrond::dout().putLn("Example::onInit");

    this->getLoopControl().time = 100;
    if(cfg.isBool("allowLoop")) this->getLoopControl().allow = cfg.asBool("allowLoop");
    if(cfg.isBool("asyncLoop")) this->getLoopControl().async = cfg.asBool("asyncLoop");
    if(cfg.isInt("timeLoop")) this->getLoopControl().time = cfg.asInt("timeLoop");
}

void Example::onStart() {
    elrond::dout().putLn("Example::onStart");
}

void Example::loop() {
    elrond::dout().put("Example::loop");
    if(this->getLoopControl().async) elrond::dout().putLn(" (async)");
    else elrond::dout().putLn(" (sync)");
}

void Example::onStop() {
    elrond::dout().putLn("Example::onStop");
}

#if defined GENERIC_STD_PLATFORM
    const char *Example::_getInternalName(){
        return "elrond::Example";
    }

    const char *Example::_infoMainClassName(){
        return "Example";
    }

    int Example::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int Example::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *Example::_infoPrettyName(){
        return "Example";
    }

    const char *Example::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *Example::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *Example::_infoVersion(){
        return "1.0";
    }
#endif
