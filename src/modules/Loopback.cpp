#include "modules/Loopback.hpp"
#include "interfaces/ConfigMapInterface.hpp"
#include "runtime/channel/BaseChannelManager.hpp"

using namespace elrond::modules;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ConfigMapInterface;
using elrond::channel::BaseChannelManager;

/*  ****************************************************************************
    ************** Implementation for elrond::modules::Loopback ****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    Loopback::~Loopback(){}
#endif

void Loopback::onInit(ConfigMapInterface &cfg){
    this->getLoopControl().allow = false;
}

void Loopback::send(elrond::byte data[], const elrond::sizeT length){

    if(this->cm == nullptr) return;

    const elrond::sizeT bufferLen = this->cm->getRxBufferSize();
    elrond::byte rxBuffer[bufferLen];

    for(elrond::sizeT i = 0; i < bufferLen; ++i){
        if(i >= length) break;
        rxBuffer[i] = data[i];
    }

    this->cm->onReceive(rxBuffer, bufferLen);
}

void Loopback::setChannelManager(BaseChannelManager *cm){
    if(this->cm == nullptr) this->cm = cm;
}

#if defined GENERIC_STD_PLATFORM

    const char *Loopback::_getInternalName(){
        return "elrond::Loopback";
    }

    const char *Loopback::_infoMainClassName(){
        return "Loopback";
    }

    int Loopback::_infoApiVersion(){
        return ELROND_API_VERSION;
    }

    int Loopback::_infoApiRevision(){
        return ELROND_API_REVISION;
    }

    const char *Loopback::_infoPrettyName(){
        return "Loopback Transport";
    }

    const char *Loopback::_infoAuthorName(){
        return "Edwino Stein";
    }

    const char *Loopback::_infoAuthorEmail(){
        return "edwino.stein@gmail.com";
    }

    const char *Loopback::_infoVersion(){
        return "1.0";
    }

#endif
