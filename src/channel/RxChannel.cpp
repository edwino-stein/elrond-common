#include "channel/RxChannel.hpp"
#include "channel/BaseChannelManager.hpp"
#include "interface/Runtime.hpp"

/*  ****************************************************************************
    ***************** elrond::channel::RxChannel Implementation ****************
    ****************************************************************************/

namespace elrond {
    namespace channel {

        ELROND_INLINE_FUNC RxChannel::RxChannel() : _data(0), data(_data) {}

        ELROND_INLINE_FUNC void RxChannel::init(
            const elrond::sizeT chId,
            const elrond::sizeT chm,
            OnReceiveHandleT handle,
            TaskContext* const ctx
        ){
            BaseChannelManager& cm = elrond::app().getChannelManager(chm);
            cm.addRxListener(chId, this);
            this->handle = handle;
            this->ctx = ctx;
        }

        ELROND_INLINE_FUNC void RxChannel::trigger(const elrond::word data)
        {
            if(this->_data == data) return;
            this->_data = data;
            this->handle(data, this->ctx);
        }
    }
}
