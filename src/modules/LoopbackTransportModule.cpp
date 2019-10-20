#include "modules/LoopbackTransportModule.hpp"
#include "runtime/config/ConfigMap.hpp"
#include "runtime/channel/BaseChannelManager.hpp"

using namespace elrond::modules;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::config::ConfigMap;
using elrond::channel::BaseChannelManager;

/*  ****************************************************************************
    ******* Implementation for elrond::modules::LoopbackTransportModule ********
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    LoopbackTransportModule::~LoopbackTransportModule(){}
#endif

void LoopbackTransportModule::onInit(elrond::config::ConfigMap &cfg){
    this->getLoopControl().allow = false;
}

void LoopbackTransportModule::send(elrond::byte data[], const elrond::sizeT length){

    if(this->cm == nullptr) return;

    const elrond::sizeT bufferLen = this->cm->getRxBufferSize();
    elrond::byte rxBuffer[bufferLen];

    for(elrond::sizeT i = 0; i < bufferLen; ++i){
        if(i >= length) break;
        rxBuffer[i] = data[i];
    }

    this->cm->onReceive(rxBuffer, bufferLen);
}

void LoopbackTransportModule::setChannelManager(BaseChannelManager *cm){
    if(this->cm == nullptr) this->cm = cm;
}

const char *LoopbackTransportModule::_getInternalName(){
    return "elrond::LoopbackTransportModule";
}

const char *LoopbackTransportModule::_infoMainClassName(){
    return "LoopbackTransportModule";
}

int LoopbackTransportModule::_infoApiVersion(){
    return ELROND_API_VERSION;
}

int LoopbackTransportModule::_infoApiRevision(){
    return ELROND_API_REVISION;
}

const char *LoopbackTransportModule::_infoPrettyName(){
    return "Loopback Transport Module";
}

const char *LoopbackTransportModule::_infoAuthorName(){
    return "Edwino Stein";
}

const char *LoopbackTransportModule::_infoAuthorEmail(){
    return "edwino.stein@gmail.com";
}

const char *LoopbackTransportModule::_infoVersion(){
    return "1.0";
}
