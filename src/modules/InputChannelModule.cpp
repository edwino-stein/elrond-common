#include "modules/InputChannelModule.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "runtime/config/ConfigMap.hpp"

using namespace elrond::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;
using elrond::channel::TxChannel;
using elrond::input::InputCallback;

/*  ****************************************************************************
    ********** Implementation for elrond::modules::InputChannelModule **********
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    InputChannelModule::~InputChannelModule(){}
#endif

void InputChannelModule::onInit(ConfigMap &cfg){

    this->getLoopControl().allow = false;

    if(!cfg.isInt("channel")) elrond::error("Invalid or missing key \"channel\".");
    int ch = cfg.asInt("channel");

    if(!cfg.isInt("input")) elrond::error("Invalid or missing key \"input\".");
    int input = cfg.asInt("input");

    int chm = 0;
    if(cfg.isInt("chm")) chm = cfg.asInt("chm");

    int inServ = 0;
    if(cfg.isInt("ins")) inServ = cfg.asInt("ins");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->txCh.init(ch, chm);
    this->inKey.init(input, inServ, [](elrond::word data, elrond::TaskContext *ctx){
        InputChannelModule *me = (InputChannelModule *) ctx;
        me->txCh.trigger(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

const char *InputChannelModule::_getInternalName(){
    return "elrond::InputChannelModule";
}

const char *InputChannelModule::_infoMainClassName(){
    return "InputChannelModule";
}

int InputChannelModule::_infoApiVersion(){
    return ELROND_API_VERSION;
}

int InputChannelModule::_infoApiRevision(){
    return ELROND_API_REVISION;
}

const char *InputChannelModule::_infoPrettyName(){
    return "Input Channel Module";
}

const char *InputChannelModule::_infoAuthorName(){
    return "Edwino Stein";
}

const char *InputChannelModule::_infoAuthorEmail(){
    return "edwino.stein@gmail.com";
}

const char *InputChannelModule::_infoVersion(){
    return "1.0";
}

