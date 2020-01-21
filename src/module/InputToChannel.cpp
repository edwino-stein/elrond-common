#include "module/InputToChannel.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::InputToChannel;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::TxChannel;
using elrond::input::InputCallback;
using elrond::LoopControl;

/*  ****************************************************************************
    *************** elrond::module::InputToChannel Implementation **************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    InputToChannel::~InputToChannel(){}
#endif

void InputToChannel::onInit(ConfigMap& cfg, LoopControl& lc)
{
    if(!cfg.isInt("channel")) elrond::error("Invalid or missing key \"channel\".");
    const int ch = cfg.asInt("channel");

    if(!cfg.isInt("input")) elrond::error("Invalid or missing key \"input\".");
    const int input = cfg.asInt("input");

    int chm = 0;
    if(cfg.isInt("chm")) chm = cfg.asInt("chm");

    int inServ = 0;
    if(cfg.isInt("ins")) inServ = cfg.asInt("ins");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->txCh.init(ch, chm);

    this->inKey.init(
        input,
        inServ,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            InputToChannel* const me = (InputToChannel*) ctx;
            me->txCh.trigger(me->inverted ? HIGH_VALUE - data : data);
        },
        this
    );
}

#ifdef ELROND_WITH_MODULES_INFO

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
