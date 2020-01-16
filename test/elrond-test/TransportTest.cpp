#include "elrond-test/TransportTest.hpp"

using elrond::test::TransportTest;
using elrond::modules::BaseTransportModule;
using elrond::modules::BaseInputDriverModule;
using elrond::channel::BaseChannelManager;

TransportTest::TransportTest(onActionT onSend, onActionT onReceive)
{
    if(onSend == nullptr){
        this->onSend = [](elrond::byte data[], const elrond::sizeT length, TransportTest& me)
        {
            me.receive(data, length);
        };
    }
    else {
        this->onSend = onSend;
    }

    if(onReceive == nullptr){
        this->onReceive = [](elrond::byte data[], const elrond::sizeT length, TransportTest& me)
        {
            me.notifyChm(data, length);
        };
    }
    else {
        this->onReceive = onReceive;
    }
}

void TransportTest::send(elrond::byte data[], const elrond::sizeT length)
{
    this->onSend(data, length, *this);
}

void TransportTest::receive(elrond::byte data[], const elrond::sizeT length)
{
    this->onReceive(data, length, *this);
}

void TransportTest::notifyChm(elrond::byte data[], const elrond::sizeT length) const
{
    if(this->cm != nullptr) this->cm->onReceive(data, length);
}

void TransportTest::setChannelManager(BaseChannelManager* cm)
{
    this->cm = cm;
}
