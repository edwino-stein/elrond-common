#include "runtime/channel/RxChannel.hpp"
#include "runtime/channel/BaseChannelManager.hpp"
#include "interfaces/RuntimeInterface.hpp"

using elrond::channel::BaseChannelManager;
using elrond::channel::RxChannel;
using elrond::channel::onReceiveT;
using elrond::TaskContext;

/*  ****************************************************************************
    ************** Implementation for elrond::channel::RxChannel ***************
    ****************************************************************************/

RxChannel::RxChannel() : _data(0), data(_data) {}

void RxChannel::init(const elrond::sizeT chId, const elrond::sizeT chm, onReceiveT handle, TaskContext *ctx){
    BaseChannelManager &cm = elrond::app().getChannelManager(chm);
    cm.addRxListener(chId, this);
    this->handle = handle;
    this->ctx = ctx;
}

void RxChannel::trigger(const elrond::word data){
    if(this->_data == data) return;
    this->_data = data;
    this->handle(data, this->ctx);
}
