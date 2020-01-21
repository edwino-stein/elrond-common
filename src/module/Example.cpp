#include "module/Example.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"
#include "interface/DebugOut.hpp"

using elrond::module::Example;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::LoopControl;

/*  ****************************************************************************
    ****************** elrond::module::Example Implementation ******************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    Example::~Example(){}
#endif

void Example::onInit(ConfigMap& cfg, LoopControl& lc)
{
    elrond::dout().putLn("Example::onInit");

    lc.interval = 100;
    if(cfg.isBool("loop")) lc.enable = cfg.asBool("loop");
    if(cfg.isBool("thread")) lc.ownThread = cfg.asBool("thread");
    if(cfg.isInt("interval")) lc.interval = cfg.asInt("interval");
}

void Example::onStart() {
    elrond::dout().putLn("Example::onStart");
}

void Example::loop() {
    elrond::dout().putLn("Example::loop");
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
