#include "modules/AnalogLed.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "interfaces/DebugOutInterface.hpp"
#include "interfaces/ConfigMapInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ConfigMapInterface;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    ************* Implementation for elrond::modules::AnalogLed ****************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    AnalogLed::~AnalogLed(){}
#endif

void AnalogLed::onInit(ConfigMapInterface &cfg){

    this->getLoopControl().allow = false;

    if(!cfg.isInt("channel")) elrond::error("Invalid or missing key \"channel\".");
    int ch = cfg.asInt("channel");

    if(!cfg.isInt("pin")) elrond::error("Invalid or missing key \"pin\".");
    int pin = cfg.asInt("pin");

    int chm = 0;
    if(cfg.isInt("chm")) chm = cfg.asInt("chm");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->pin.attach(pin);
    this->ch.init(ch, chm, [](elrond::word data, elrond::TaskContext *ctx){
        AnalogLed *me = (AnalogLed *) ctx;
        me->pin.write(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

#if defined GENERIC_STD_PLATFORM

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
