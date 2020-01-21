#include "module/Servo.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using ServoModule = elrond::module::Servo;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::RxChannel;
using elrond::LoopControl;

/*  ****************************************************************************
    ******************* elrond::module::Servo Implementation *******************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    ServoModule::~Servo(){}
#endif

void ServoModule::onInit(ConfigMap& cfg, LoopControl& lc)
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
            ServoModule* const me = (ServoModule *) ctx;
            me->pin.write(me->inverted ? HIGH_VALUE - data : data);
        },
        this
    );
}

#ifdef ELROND_WITH_MODULES_INFO

    const char *ServoModule::_getInternalName(){
        return "elrond::Servo";
    }

    const char *ServoModule::_infoMainClassName(){
        return "Servo";
    }

    int ServoModule::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int ServoModule::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *ServoModule::_infoPrettyName(){
        return "Servo";
    }

    const char *ServoModule::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *ServoModule::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *ServoModule::_infoVersion(){
        return "1.0";
    }

#endif
