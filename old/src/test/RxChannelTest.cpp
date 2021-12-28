#include "test/RxChannelTest.hpp"

using elrond::test::RxChannelTest;
using elrond::channel::RxChannel;
using elrond::channel::BaseChannelManager;
using elrond::channel::OnReceiveHandleT;

RxChannelTest::RxChannelTest(
    const elrond::sizeT ch,
    OnReceiveHandleT handle,
    BaseChannelManager& chm
){
    this->_ch = ch;
    this->handle = handle;
    chm.addRxListener((RxChannel*) this);
}

RxChannelTest::RxChannelTest(
    const elrond::sizeT ch,
    OnReceiveHandleT handle
){
    this->_ch = ch;
    this->handle = handle;
}
