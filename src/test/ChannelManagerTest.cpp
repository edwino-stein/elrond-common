#include "test/ChannelManagerTest.hpp"
#include "test/RxChannelTest.hpp"
#include "test/TxChannelTest.hpp"

using elrond::test::ChannelManagerTest;
using elrond::test::RxChannelTest;
using elrond::channel::BaseChannelManager;
using elrond::channel::TxChannel;
using elrond::channel::RxChannel;
using elrond::channel::OnReceiveHandleT;
using elrond::channel::BufferWrapper;
using elrond::module::BaseDataLinkModule;

ChannelManagerTest::ChannelManagerTest(
    BaseDataLinkModule& dataLink,
    const elrond::sizeT chs
):
    BaseChannelManager(dataLink),
    chs(chs),
    txBuffer(new elrond::byte[ELROND_PROTOCOL_CALC_BUFFER(chs)]),
    rxChannels(new RxChCollectionP[chs])
{
    for(elrond::sizeT i = 0; i < chs; ++i) this->rxChannels[i] = nullptr;
    this->init();
}

void ChannelManagerTest::txTrigger(TxChannel* const tx)
{ BaseChannelManager::txTrigger(tx); }

void ChannelManagerTest::addRxListener(RxChannel* const rx)
{
    if(rx->ch >= this->chs) return;

    if(this->rxChannels[rx->ch] == nullptr)
        this->rxChannels[rx->ch] = RxChCollectionP(new RxChCollection());

    this->rxChannels[rx->ch]->push_back(rx);
}

void ChannelManagerTest::addRxListener(RxChannelTest &rx)
{ this->addRxListener((RxChannel*) &rx); }

void ChannelManagerTest::rxTrigger(const elrond::sizeT ch, const elrond::word data)
{
    if(ch >= this->chs) return;
    if(this->rxChannels[ch] == nullptr) return;

    RxChCollection& channels = *(this->rxChannels[ch]);
    for (auto &rxCh : channels) rxCh->trigger(data);
}

BufferWrapper ChannelManagerTest::getTxBuffer() const {
    BufferWrapper txBuffer(this->txBuffer.get(), this->getTxBufferSize());
    return txBuffer;
}

elrond::sizeT ChannelManagerTest::getTotalTx() const { return this->chs; }
elrond::sizeT ChannelManagerTest::getTotalRx() const { return this->chs; }
