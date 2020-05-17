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
            me->txCh.trigger(me->inverted ? elrond::high - data : data);
        },
        this
    );
}

ELROND_DEFINE_INTER_MOD(
    elrond::InputToChannel,
    "Input to Channel",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
