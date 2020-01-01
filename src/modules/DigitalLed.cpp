#include "modules/DigitalLed.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "interfaces/DebugOutInterface.hpp"
#include "interfaces/ConfigMapInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ConfigMapInterface;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    ************* Implementation for elrond::modules::DigitalLed ***************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    DigitalLed::~DigitalLed(){}
#endif

void DigitalLed::onInit(ConfigMapInterface &cfg){

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
        DigitalLed *me = (DigitalLed *) ctx;
        me->pin.write(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

#if defined GENERIC_STD_PLATFORM

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
