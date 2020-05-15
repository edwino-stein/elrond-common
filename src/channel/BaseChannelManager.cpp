#include "channel/BaseChannelManager.hpp"
#include "channel/RxChannel.hpp"
#include "channel/TxChannel.hpp"

using elrond::channel::BaseChannelManager;
using elrond::module::BaseDataLinkModule;
using elrond::channel::TxChannel;
using elrond::channel::RxChannel;
using elrond::channel::OnChmReceiveHandleT;
using elrond::channel::BufferWrapper;

/*  ****************************************************************************
    ************ elrond::channel::BaseChannelManager Implementation ************
    ****************************************************************************/

BaseChannelManager::BaseChannelManager(BaseDataLinkModule& dataLink):
dataLink(dataLink) { this->dataLink.setCHM(this); }

#ifdef ELROND_WITH_DESTRUCTORS
    BaseChannelManager::~BaseChannelManager(){}
#endif

void BaseChannelManager::init()
{
    BufferWrapper txBuffer = this->getTxBuffer();

    if(txBuffer.length < ELROND_PROTOCOL_HEADER_SIZE) return;

    txBuffer.data[ELROND_PROTOCOL_HEAD_BYTE_ACTION] = ELROND_PROTOCOL_ACTION_UPDATE_CHANNEL;
    txBuffer.data[ELROND_PROTOCOL_HEAD_HWORD_HBYTE_SEQ] = 0;
    txBuffer.data[ELROND_PROTOCOL_HEAD_HWORD_LBYTE_SEQ] = 0;
    txBuffer.data[ELROND_PROTOCOL_HEAD_LWORD_HBYTE_SEQ] = 0;
    txBuffer.data[ELROND_PROTOCOL_HEAD_LWORD_LBYTE_SEQ] = 0;

    const elrond::sizeT totalCh = this->getTotalTx();
    txBuffer.data[ELROND_PROTOCOL_TOTAL_CH_BYTE] = elrond::lowByte(totalCh);

    elrond::sizeT offset = ELROND_PROTOCOL_BODY_FIRST_BYTE;
    for(elrond::sizeT i = 0; i < totalCh; ++i){
        if(offset >= txBuffer.length) break;
        ELROND_GET_CH_INDEX(txBuffer.data, offset) = elrond::lowByte(i);
        ELROND_GET_CH_DATA_HB(txBuffer.data, offset) = 0;
        ELROND_GET_CH_DATA_LB(txBuffer.data, offset) = 0;
        offset += ELROND_PROTOCOL_BYTES_PER_CHANNEL;
    }
}

void BaseChannelManager::txTrigger(TxChannel* const tx)
{
    const elrond::sizeT ch = tx->ch;
    const elrond::word data = tx->data;

    if(ch >= this->getTotalTx()) return;

    BufferWrapper txBuffer = this->getTxBuffer();
    const elrond::sizeT offset = ELROND_CALC_CH_OFFSET(ch);

    ELROND_GET_CH_DATA_HB(txBuffer.data, offset) = elrond::highByte(data);
    ELROND_GET_CH_DATA_LB(txBuffer.data, offset) = elrond::lowByte(data);

    this->hasTxUpdate = true;
}

void BaseChannelManager::tryReceive(OnChmReceiveHandleT handle, elrond::TaskContext* const ctx)
{
    const elrond::sizeT bufLen = this->getRxBufferSize();
    elrond::byte data[bufLen];
    const elrond::sizeT received = (handle != nullptr) ? handle(data, bufLen, ctx) : 0;

    if(received <= ELROND_PROTOCOL_HEADER_SIZE || received != bufLen) return;
    if(data[ELROND_PROTOCOL_HEAD_BYTE_ACTION] != ELROND_PROTOCOL_ACTION_UPDATE_CHANNEL) return;

    const elrond::sizeT totalCh = (elrond::sizeT) data[ELROND_PROTOCOL_TOTAL_CH_BYTE];
    if(totalCh != this->getTotalRx()) return;

    elrond::sizeT offset = ELROND_PROTOCOL_BODY_FIRST_BYTE;
    for(elrond::sizeT i = 0; i < totalCh; ++i){

        if(offset >= bufLen) break;

        this->rxTrigger(
            ELROND_GET_CH_INDEX(data, offset),
            elrond::makeWord(
                ELROND_GET_CH_DATA_HB(data, offset),
                ELROND_GET_CH_DATA_LB(data, offset)
            )
        );

        offset += ELROND_PROTOCOL_BYTES_PER_CHANNEL;
    }
}

bool BaseChannelManager::txSync(const bool tryForce)
{
    if(!(this->hasTxUpdate || tryForce)) return false;

    BufferWrapper txBuffer = this->getTxBuffer();
    if(this->dataLink.send(txBuffer.data, txBuffer.length)){
        this->hasTxUpdate = false;
        return true;
    }

    return false;
}

elrond::sizeT BaseChannelManager::getRxBufferSize() const
{ return ELROND_PROTOCOL_CALC_BUFFER(this->getTotalRx()); }

elrond::sizeT BaseChannelManager::getTxBufferSize() const
{ return ELROND_PROTOCOL_CALC_BUFFER(this->getTotalTx()); }
