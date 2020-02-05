#include "module/DigitalLed.hpp"
#include "interface/Runtime.hpp"
#include "interface/DebugOut.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::DigitalLed;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::RxChannel;
using elrond::LoopControl;

/*  ****************************************************************************
    **************** elrond::module::DigitalLed Implementation *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    DigitalLed::~DigitalLed(){}
#endif

void DigitalLed::onInit(ConfigMap &cfg, LoopControl& lc)
{
    if(!cfg.isInt("channel")) elrond::error("Invalid or missing key \"channel\".");
    const int ch = cfg.asInt("channel");

    if(!cfg.isInt("pin")) elrond::error("Invalid or missing key \"pin\".");
    const int pin = cfg.asInt("pin");

    int chm = 0;
    if(cfg.isInt("chm")) chm = cfg.asInt("chm");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->pin.attach(pin);

    this->ch.init(
        ch,
        chm,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            DigitalLed* const me = (DigitalLed*) ctx;
            me->pin.write(me->inverted ? HIGH_VALUE - data : data);
        },
        this
    );
}

ELROND_DEFINE_INTER_MOD(
    elrond::DigitalLed,
    "Digital LED",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
