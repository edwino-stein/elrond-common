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

#ifdef ELROND_WITH_MODULES_INFO

    const char *DigitalLed::_getInternalName(){
        return "elrond::DigitalLed";
    }

    const char *DigitalLed::_infoMainClassName(){
        return "DigitalLed";
    }

    int DigitalLed::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int DigitalLed::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *DigitalLed::_infoPrettyName(){
        return "Digital LED";
    }

    const char *DigitalLed::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *DigitalLed::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *DigitalLed::_infoVersion(){
        return "1.0";
    }

#endif
