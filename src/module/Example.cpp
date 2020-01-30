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

ELROND_DEFINE_INTER_MOD(
    elrond::Example,
    "Example",
    "Edwino Stein",
    "edwino.stein@gmail.com",
    ELROND_TO_STR_CONCAT(ELROND_API_VERSION.ELROND_API_REVISION-ELROND_API_DEVSTATE)
)
