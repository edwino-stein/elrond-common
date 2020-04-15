#include "channel/RxChannel.hpp"
#include "interface/ChannelManager.hpp"
#include "interface/Runtime.hpp"

/*  ****************************************************************************
    ***************** elrond::channel::RxChannel Implementation ****************
    ****************************************************************************/

namespace elrond {
    namespace channel {

        ELROND_INLINE_FUNC RxChannel::RxChannel() : Channel(){}

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC RxChannel::~RxChannel(){}
        #endif

        ELROND_INLINE_FUNC void RxChannel::init(
            const elrond::sizeT ch,
            const elrond::sizeT chm,
            OnReceiveHandleT handle,
            TaskContext* const ctx
        ){
            if(this->handle != nullptr) return;
            elrond::interface::ChannelManager& cm = elrond::app().getChannelManager(chm);
            cm.addRxListener(ch, this);
            this->_ch = ch;
            this->handle = handle;
            this->ctx = ctx;
        }

        ELROND_INLINE_FUNC void RxChannel::trigger(const elrond::word data)
        {
            if(this->handle == nullptr) return;
            if(this->_data == data) return;
            this->_data = data;
            this->handle(data, this->ctx);
        }
    }
}
