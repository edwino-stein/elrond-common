#include "test/TxChannelTest.hpp"

using elrond::test::TxChannelTest;
using elrond::channel::TxChannel;
using elrond::channel::BaseChannelManager;
using elrond::interface::ChannelManager;

TxChannelTest::TxChannelTest(const elrond::sizeT ch, BaseChannelManager& chm)
{
    this->_ch = ch;
    this->chm = (ChannelManager*) &chm;
}
