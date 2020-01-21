#include "module/AnalogLed.hpp"
#include "interface/Runtime.hpp"
#include "interface/DebugOut.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::AnalogLed;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    ***************** elrond::module::AnalogLed Implementation *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    AnalogLed::~AnalogLed(){}
#endif

void AnalogLed::onInit(ConfigMap &cfg)
{
    this->getLoopControl().allow = false;

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
            AnalogLed* const me = (AnalogLed*) ctx;
            me->pin.write(me->inverted ? HIGH_VALUE - data : data);
        },
        this
    );
}

#ifdef ELROND_WITH_MODULES_INFO

    const char *AnalogLed::_getInternalName(){
        return "elrond::AnalogLed";
    }

    const char *AnalogLed::_infoMainClassName(){
        return "AnalogLed";
    }

    int AnalogLed::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int AnalogLed::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *AnalogLed::_infoPrettyName(){
        return "Analog LED";
    }

    const char *AnalogLed::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *AnalogLed::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *AnalogLed::_infoVersion(){
        return "1.0";
    }

#endif
