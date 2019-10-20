#include "runtime/channel/BaseChannelManager.hpp"
#include "modules/BaseTransportModule.hpp"
using elrond::channel::BaseChannelManager;
using elrond::modules::BaseTransportModule;

/*  ****************************************************************************
    ********** Implementation for elrond::channel::BaseChannelManager **********
    ****************************************************************************/

BaseChannelManager::BaseChannelManager(BaseTransportModule &transport): transport(transport){
    this->transport.setChannelManager(this);

}
