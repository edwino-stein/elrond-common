#include "module/Loopback.hpp"
#include "interface/ConfigMap.hpp"
#include "channel/BaseChannelManager.hpp"

using elrond::module::Loopback;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::channel::BaseChannelManager;
using elrond::LoopControl;

/*  ****************************************************************************
    ****************** elrond::module::Loopback Implementation *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    Loopback::~Loopback(){}
#endif

void Loopback::send(elrond::byte data[], const elrond::sizeT length)
{
    if(this->cm == nullptr) return;

    const elrond::sizeT bufferLen = this->cm->getRxBufferSize();
    elrond::byte rxBuffer[bufferLen];

    for(elrond::sizeT i = 0; i < bufferLen; ++i){
        if(i >= length) break;
        rxBuffer[i] = data[i];
    }

    this->cm->onReceive(rxBuffer, bufferLen);
}

void Loopback::setChannelManager(BaseChannelManager* cm)
{
    if(this->cm == nullptr) this->cm = cm;
}

ELROND_DEFINE_INTER_MOD(
    elrond::Loopback,
    "Loopback Transport",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
