#include "interface/Runtime.hpp"
#include "interface/Module.hpp"
#include "interface/ConfigMap.hpp"
#include "interface/DebugOut.hpp"
#include "interface/ChannelManager.hpp"
#include "interface/Channel.hpp"

/*  ****************************************************************************
    *************************** elrond implementation **************************
    ****************************************************************************/
#ifndef ELROND_WITH_INLINE_FUNC
    ELROND_MOD_INFO_APP_P ELROND_MOD_APP_VAR = nullptr;
#endif

namespace elrond {

    ELROND_INLINE_FUNC interface::Runtime& app()
    { return *(ELROND_MOD_APP_VAR); }

    ELROND_INLINE_FUNC const interface::DebugOut& dout()
    { return elrond::app().dout(); }

    ELROND_INLINE_FUNC void error(const char* error)
    { app().onError(error); }

    #ifdef ELROND_WITH_STR_TYPE
        ELROND_INLINE_FUNC void error(elrond::String error)
        { app().onError(error); }
    #endif

}

/*  ****************************************************************************
    **************** elrond::interface classes implementations *****************
    ****************************************************************************/
namespace elrond {
    namespace interface {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC Module::~Module(){}
            ELROND_INLINE_FUNC ChannelManager::~ChannelManager(){}
            ELROND_INLINE_FUNC Channel::~Channel(){}
        #endif

        ELROND_INLINE_FUNC Channel::Channel() : ch(_ch), data(_data) {}
    }
}
