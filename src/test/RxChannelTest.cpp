#include "test/RxChannelTest.hpp"

using elrond::test::RxChannelTest;
using elrond::channel::RxChannel;
using elrond::channel::BaseChannelManager;
using elrond::channel::OnReceiveHandleT;

RxChannelTest::RxChannelTest(
    const elrond::sizeT ch,
    OnReceiveHandleT handle,
    BaseChannelManager& chm
):
    RxChannel()
{
    this->_ch = ch;
    this->handle = handle;
    chm.addRxListener((RxChannel*) this);
}

RxChannelTest::RxChannelTest(
    const elrond::sizeT ch,
    OnReceiveHandleT handle
):
    RxChannel()
{
    this->_ch = ch;
    this->handle = handle;
}
