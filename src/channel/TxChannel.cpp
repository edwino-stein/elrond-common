#include "channel/TxChannel.hpp"
#include "channel/BaseChannelManager.hpp"
#include "interfaces/RuntimeInterface.hpp"

using elrond::channel::BaseChannelManager;
using elrond::channel::TxChannel;

/*  ****************************************************************************
    **************** elrond::channel::TxChannel Implementation *****************
    ****************************************************************************/

void TxChannel::init(const elrond::sizeT chId, const sizeT chm)
{
    this->chm = &(elrond::app().getChannelManager(chm));
    this->chId = chId;
}

void TxChannel::trigger(const elrond::word data)
{
    if(this->chm == nullptr) return;
    this->chm->txTrigger(this->chId, data);
}
