#include "test/DataLinkTest.hpp"

using elrond::test::DataLinkTest;
using elrond::module::Loopback;
using elrond::module::BaseDataLinkModule;
using elrond::channel::OnChmReceiveHandleT;
using elrond::channel::BufferWrapper;

DataLinkTest::DataLinkTest(onActionT onSend, onActionT onReceive)
{
    if(onSend == nullptr){
        this->onSend = [](elrond::byte data[], const elrond::sizeT length)
        { return true; };
    }
    else {
        this->onSend = onSend;
    }

    if(onReceive == nullptr){
        this->onReceive = [](elrond::byte data[], const elrond::sizeT length)
        { return true; };
    }
    else {
        this->onReceive = onReceive;
    }
}

bool DataLinkTest::send(elrond::byte data[], const elrond::sizeT length)
{ return this->onSend(data, length) ? Loopback::send(data, length) : false; }

void DataLinkTest::receive(OnChmReceiveHandleT handle, elrond::TaskContext* const ctx)
{
    BufferWrapper* const txb = (BufferWrapper* const) ctx;
    if(this->onReceive(txb->data, txb->length))
        BaseDataLinkModule::receive(handle, ctx);
}
