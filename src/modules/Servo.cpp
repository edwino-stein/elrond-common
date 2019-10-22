#include "modules/Servo.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "runtime/config/ConfigMap.hpp"

using namespace elrond::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    **************** Implementation for elrond::modules::Servo *****************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    Servo::~Servo(){}
#endif

void Servo::onInit(ConfigMap &cfg){

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
        Servo *me = (Servo *) ctx;
        me->pin.write(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

const char *Servo::_getInternalName(){
    return "elrond::Servo";
}

const char *Servo::_infoMainClassName(){
    return "Servo";
}

int Servo::_infoApiVersion(){
    return ELROND_API_VERSION;
}

int Servo::_infoApiRevision(){
    return ELROND_API_REVISION;
}

const char *Servo::_infoPrettyName(){
    return "Servo";
}

const char *Servo::_infoAuthorName(){
    return "Edwino Stein";
}

const char *Servo::_infoAuthorEmail(){
    return "edwino.stein@gmail.com";
}

const char *Servo::_infoVersion(){
    return "1.0";
}

