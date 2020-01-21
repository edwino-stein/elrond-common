#include "channel/RxChannel.hpp"
#include "channel/BaseChannelManager.hpp"
#include "interfaces/RuntimeInterface.hpp"

using elrond::channel::BaseChannelManager;
using elrond::channel::RxChannel;
using elrond::channel::OnReceiveHandleT;
using elrond::TaskContext;

/*  ****************************************************************************
    ***************** elrond::channel::RxChannel Implementation ****************
    ****************************************************************************/

RxChannel::RxChannel() : _data(0), data(_data) {}

void RxChannel::init(
    const elrond::sizeT chId,
    const elrond::sizeT chm,
    OnReceiveHandleT handle,
    TaskContext* const ctx
){
    BaseChannelManager& cm = elrond::app().getChannelManager(chm);
    cm.addRxListener(chId, this);
    this->handle = handle;
    this->ctx = ctx;
}

void RxChannel::trigger(const elrond::word data)
{
    if(this->_data == data) return;
    this->_data = data;
    this->handle(data, this->ctx);
}
