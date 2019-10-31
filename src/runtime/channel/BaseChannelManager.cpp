#include "runtime/channel/BaseChannelManager.hpp"
#include "modules/BaseTransportModule.hpp"
#include "runtime/channel/RxChannel.hpp"
#include "runtime/channel/TxChannel.hpp"
#include "runtime/bitwise.hpp"

using elrond::channel::BaseChannelManager;
using elrond::modules::BaseTransportModule;
using elrond::channel::TxChannel;
using elrond::channel::RxChannel;

/*  ****************************************************************************
    ********** Implementation for elrond::channel::BaseChannelManager **********
    ****************************************************************************/

BaseChannelManager::BaseChannelManager(BaseTransportModule &transport): transport(transport){
    this->transport.setChannelManager(this);
}

void BaseChannelManager::init(){

    const elrond::sizeT length = this->getTxBufferSize();
    if(length < ELROND_PROTOCOL_HEADER_SIZE) return;

    elrond::byte *txBuffer = this->getTxBuffer();
    txBuffer[ELROND_PROTOCOL_HEAD_BYTE_ACTION] = ELROND_PROTOCOL_ACTION_UPDATE_CHANNEL;
    txBuffer[ELROND_PROTOCOL_HEAD_HWORD_HBYTE_SEQ] = 0;
    txBuffer[ELROND_PROTOCOL_HEAD_HWORD_LBYTE_SEQ] = 0;
    txBuffer[ELROND_PROTOCOL_HEAD_LWORD_HBYTE_SEQ] = 0;
    txBuffer[ELROND_PROTOCOL_HEAD_LWORD_LBYTE_SEQ] = 0;


    const elrond::sizeT totalCh = this->getTotalTx();
    txBuffer[ELROND_PROTOCOL_TOTAL_CH_BYTE] = elrond::lowByte(totalCh);

    elrond::sizeT offset = ELROND_PROTOCOL_BODY_FIRST_BYTE;
    for(elrond::sizeT i = 0; i < totalCh; ++i){
        if(offset >= length) break;
        ELROND_GET_CH_INDEX(txBuffer, offset) = elrond::lowByte(i);
        ELROND_GET_CH_DATA_HB(txBuffer, offset) = 0;
        ELROND_GET_CH_DATA_LB(txBuffer, offset) = 0;
        offset += ELROND_PROTOCOL_BYTES_PER_CHANNEL;
    }
}

void BaseChannelManager::txTrigger(const elrond::sizeT ch, const elrond::word data){

    if(ch >= this->getTotalTx()) return;

    elrond::byte *txBuffer = this->getTxBuffer();
    const elrond::sizeT offset = ELROND_CALC_CH_OFFSET(ch);
    ELROND_GET_CH_DATA_HB(txBuffer, offset) = elrond::highByte(data);
    ELROND_GET_CH_DATA_LB(txBuffer, offset) = elrond::lowByte(data);

    this->hasTxUpdate = true;
}

bool BaseChannelManager::txSync(const bool force){
    if(!(this->hasTxUpdate || force)) return false;
    this->transport.send(this->getTxBuffer(), this->getTxBufferSize());
    this->hasTxUpdate = false;
    return true;
}

void BaseChannelManager::onReceive(elrond::byte data[], const elrond::sizeT length){

    if(length <= ELROND_PROTOCOL_HEADER_SIZE || length != this->getRxBufferSize()) return;
    if(data[ELROND_PROTOCOL_HEAD_BYTE_ACTION] != ELROND_PROTOCOL_ACTION_UPDATE_CHANNEL) return;

    const elrond::sizeT totalCh = (elrond::sizeT) data[ELROND_PROTOCOL_TOTAL_CH_BYTE];
    if(totalCh != this->getTotalRx()) return;

    elrond::sizeT offset = ELROND_PROTOCOL_BODY_FIRST_BYTE;
    for(elrond::sizeT i = 0; i < totalCh; ++i){

        if(offset >= length) break;

        this->rxTrigger(
            ELROND_GET_CH_INDEX(data, offset),
            elrond::makeWord(
                ELROND_GET_CH_DATA_HB(data, offset),
                ELROND_GET_CH_DATA_HB(data, offset)
            )
        );

        offset += ELROND_PROTOCOL_BYTES_PER_CHANNEL;
    }
}

elrond::sizeT BaseChannelManager::getRxBufferSize() const {
    return ELROND_PROTOCOL_CALC_BUFFER(this->getTotalRx());
}

elrond::sizeT BaseChannelManager::getTxBufferSize() const {
    return ELROND_PROTOCOL_CALC_BUFFER(this->getTotalTx());
}
