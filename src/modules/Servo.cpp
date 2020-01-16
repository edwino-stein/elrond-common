#include "modules/Servo.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "interfaces/ConfigMapInterface.hpp"

using namespace elrond::modules;
using ServoModule = elrond::modules::Servo;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ConfigMapInterface;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    **************** Implementation for elrond::modules::Servo *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    ServoModule::~Servo(){}
#endif

void ServoModule::onInit(ConfigMapInterface &cfg){

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
        ServoModule *me = (ServoModule *) ctx;
        me->pin.write(me->inverted ? HIGH_VALUE - data : data);
    }, this);
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
