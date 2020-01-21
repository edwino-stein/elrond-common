#include "module/Example.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"
#include "interface/DebugOut.hpp"

using elrond::module::Example;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;

/*  ****************************************************************************
    ****************** elrond::module::Example Implementation ******************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    Example::~Example(){}
#endif

void Example::onInit(ConfigMap& cfg)
{
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

#ifdef ELROND_WITH_MODULES_INFO

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
