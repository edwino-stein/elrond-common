#include "modules/InputToChannel.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "runtime/config/ConfigMap.hpp"
#include "interfaces/ConfigMapInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;
using elrond::interfaces::ConfigMapInterface;
using elrond::channel::TxChannel;
using elrond::input::InputCallback;

/*  ****************************************************************************
    ************ Implementation for elrond::modules::InputToChannel ************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    InputToChannel::~InputToChannel(){}
#endif

void InputToChannel::onInit(ConfigMapInterface &cfg){

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
        InputToChannel *me = (InputToChannel *) ctx;
        me->txCh.trigger(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

#if defined GENERIC_STD_PLATFORM

    const char *InputToChannel::_getInternalName(){
        return "elrond::InputToChannel";
    }

    const char *InputToChannel::_infoMainClassName(){
        return "InputToChannel";
    }

    int InputToChannel::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int InputToChannel::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *InputToChannel::_infoPrettyName(){
        return "Input Channel Module";
    }

    const char *InputToChannel::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *InputToChannel::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *InputToChannel::_infoVersion(){
        return "1.0";
    }

#endif
