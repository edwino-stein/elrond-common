#include "module/ChannelToChannel.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

using elrond::module::ChannelToChannel;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::TxChannel;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    ************** elrond::module::ChannelToChannel Implementation *************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    ChannelToChannel::~ChannelToChannel(){}
#endif

void ChannelToChannel::onInit(ConfigMap& cfg)
{
    this->getLoopControl().allow = false;

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

    this->rxCh.init(rxCh, rxChm, [](const elrond::word data, elrond::TaskContext* const ctx){
        ChannelToChannel* const me = (ChannelToChannel*) ctx;
        me->txCh.trigger(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

#ifdef ELROND_WITH_MODULES_INFO

    const char *ChannelToChannel::_getInternalName(){
        return "elrond::ChannelToChannel";
    }

    const char *ChannelToChannel::_infoMainClassName(){
        return "ChannelToChannel";
    }

    int ChannelToChannel::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int ChannelToChannel::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *ChannelToChannel::_infoPrettyName(){
        return "Channel to Channel";
    }

    const char *ChannelToChannel::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *ChannelToChannel::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *ChannelToChannel::_infoVersion(){
        return "1.0";
    }

#endif
