#include "channel/TxChannel.hpp"
#include "interface/ChannelManager.hpp"
#include "interface/Runtime.hpp"

/*  ****************************************************************************
    **************** elrond::channel::TxChannel Implementation *****************
    ****************************************************************************/

namespace elrond {
    namespace channel {

        ELROND_INLINE_FUNC void TxChannel::init(const elrond::uInt8 ch, const sizeT chm)
        {
            if(this->chm != nullptr) return;
            this->chm = &(elrond::app().getChannelManager(chm));
            this->_ch = ch;
        }

        ELROND_INLINE_FUNC void TxChannel::trigger(const elrond::word data)
        {
            if(this->_data == data || this->chm == nullptr) return;
            this->_data = data;
            this->chm->txTrigger(this);
        }
    }
}
