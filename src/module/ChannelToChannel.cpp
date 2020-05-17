#include "module/ChannelToChannel.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::ChannelToChannel;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::TxChannel;
using elrond::channel::RxChannel;
using elrond::LoopControl;

/*  ****************************************************************************
    ************** elrond::module::ChannelToChannel Implementation *************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    ChannelToChannel::~ChannelToChannel(){}
#endif

void ChannelToChannel::onInit(ConfigMap& cfg, LoopControl& lc)
{
    if(!cfg.isInt("txCh")) elrond::error("Invalid or missing key \"txCh\".");
    const int txCh = cfg.asInt("txCh");

    if(!cfg.isInt("txChm")) elrond::error("Invalid or missing key \"txChm\".");
    const int txChm = cfg.asInt("txChm");

    if(!cfg.isInt("rxCh")) elrond::error("Invalid or missing key \"rxCh\".");
    int rxCh = cfg.asInt("rxCh");

    if(!cfg.isInt("rxChm")) elrond::error("Invalid or missing key \"rxChm\".");
    int rxChm = cfg.asInt("rxChm");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->txCh.init(txCh, txChm);

    this->rxCh.init(
        rxCh,
        rxChm,
        [](const elrond::word data, elrond::TaskContext* const ctx){
            ChannelToChannel* const me = (ChannelToChannel*) ctx;
            me->txCh.trigger(me->inverted ? elrond::high - data : data);
        },
        this
    );
}

ELROND_DEFINE_INTER_MOD(
    elrond::ChannelToChannel,
    "Channel to Channel",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
