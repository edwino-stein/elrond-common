#include "runtime/channel/TxChannel.hpp"
#include "runtime/channel/BaseChannelManager.hpp"
#include "interfaces/RuntimeInterface.hpp"

using elrond::channel::BaseChannelManager;
using elrond::channel::TxChannel;

/*  ****************************************************************************
    ************** Implementation for elrond::channel::TxChannel ***************
    ****************************************************************************/

void TxChannel::init(const elrond::sizeT chId, const sizeT chm){
    this->chm = &(elrond::app().getChannelManager(chm));
    this->chId = chId;
}

void TxChannel::trigger(const elrond::word data){
    if(this->chm == nullptr) return;
    this->chm->txTrigger(this->chId, data);
}
