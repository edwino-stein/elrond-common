#include "test/ChannelManagerTest.hpp"

using elrond::test::ChannelManagerTest;
using elrond::channel::BaseChannelManager;
using elrond::module::BaseTransportModule;
using elrond::channel::RxChannel;
using elrond::channel::OnReceiveHandleT;

ChannelManagerTest::ChannelManagerTest(
    BaseTransportModule& transport,
    const elrond::sizeT chs,
    const bool autoSync,
    const bool autoInit
):
BaseChannelManager(transport),
chs(chs),
autoSync(autoSync),
txBuffer(new elrond::byte[ELROND_PROTOCOL_CALC_BUFFER(chs)]),
rxChannels(new RxChCollectionP[chs])
{
    for(elrond::sizeT i = 0; i < chs; ++i) this->rxChannels[i] = nullptr;
    if(autoInit) this->init();
}

void ChannelManagerTest::txTrigger(const elrond::sizeT ch, const elrond::word data)
{
    BaseChannelManager::txTrigger(ch, data);
    if(this->autoSync) this->txSync(true);
}

void ChannelManagerTest::addRxListener(const elrond::sizeT ch, RxChannel *rx)
{
    if(ch >= this->chs) return;
    if(this->rxChannels[ch] == nullptr) this->rxChannels[ch] = RxChCollectionP(new RxChCollection());
    this->rxChannels[ch]->channels.push_back(rx);
}

void ChannelManagerTest::rxTrigger(const elrond::sizeT ch, const elrond::word data)
{
    if(ch >= this->chs) return;
    if(this->rxChannels[ch] == nullptr) return;

    for (auto &rxCh : this->rxChannels[ch]->channels){
        rxCh->trigger(data);
    }
}

void ChannelManagerTest::onRxReceive(const elrond::sizeT ch, OnReceiveHandleT handle)
{
    ChannelManagerTest::RxChTestP rxCh(new RxChannelTest(handle));
    this->addRxListener(ch, (RxChannel*) rxCh.get());
    this->rxChTestInsts.push_back(std::move(rxCh));
}

ChannelManagerTest::RxChannelTest::RxChannelTest(OnReceiveHandleT handle)
{
    this->handle = handle;
}

elrond::byte *ChannelManagerTest::getTxBuffer() const{ return this->txBuffer.get(); }
elrond::sizeT ChannelManagerTest::getTotalTx() const {return this->chs; }
elrond::sizeT ChannelManagerTest::getTotalRx() const {return this->chs; }
