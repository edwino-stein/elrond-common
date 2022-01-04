#include "module/Example.hpp"

using elrond::module::Example;
using elrond::interface::Module;
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
    elrond::info() << "Example::onInit" << elrond::endl;

    lc.interval = 100;
    if(cfg.isBool("loop")) lc.enable = cfg.asBool("loop");
    if(cfg.isBool("thread")) lc.ownThread = cfg.asBool("thread");
    if(cfg.isInt("interval")) lc.interval = cfg.asInt("interval");
}

void Example::onStart() { elrond::info() << "Example::onStart" << elrond::endl; }
void Example::loop() { elrond::info() << "Example::loop" << elrond::endl; }
void Example::onStop() { elrond::info() << "Example::onStop" << elrond::endl; }

ELROND_DEFINE_INTER_MOD(
    elrond::Example,
    "Example",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
