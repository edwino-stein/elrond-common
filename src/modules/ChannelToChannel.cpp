#include "modules/ChannelToChannel.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "interfaces/ConfigMapInterface.hpp"

using namespace elrond::modules;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ConfigMapInterface;
using elrond::channel::TxChannel;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    *********** Implementation for elrond::modules::ChannelToChannel ***********
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    ChannelToChannel::~ChannelToChannel(){}
#endif

void ChannelToChannel::onInit(ConfigMapInterface &cfg){

    this->getLoopControl().allow = false;

    if(!cfg.isInt("txCh")) elrond::error("Invalid or missing key \"txCh\".");
    int txCh = cfg.asInt("txCh");

    if(!cfg.isInt("txChm")) elrond::error("Invalid or missing key \"txChm\".");
    int txChm = cfg.asInt("txChm");

    if(!cfg.isInt("rxCh")) elrond::error("Invalid or missing key \"rxCh\".");
    int rxCh = cfg.asInt("rxCh");

    if(!cfg.isInt("rxChm")) elrond::error("Invalid or missing key \"rxChm\".");
    int rxChm = cfg.asInt("rxChm");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->txCh.init(txCh, txChm);

    this->rxCh.init(rxCh, rxChm, [](elrond::word data, elrond::TaskContext *ctx){
        ChannelToChannel *me = (ChannelToChannel *) ctx;
        me->txCh.trigger(me->inverted ? HIGH_VALUE - data : data);
    }, this);
}

#if defined GENERIC_STD_PLATFORM

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
