#include "channel/TxChannel.hpp"
#include "interface/ChannelManager.hpp"
#include "interface/Runtime.hpp"

/*  ****************************************************************************
    **************** elrond::channel::TxChannel Implementation *****************
    ****************************************************************************/

namespace elrond {
    namespace channel {

        ELROND_INLINE_FUNC TxChannel::TxChannel() : Channel() {}

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC TxChannel::~TxChannel(){}
        #endif

        ELROND_INLINE_FUNC void TxChannel::init(const elrond::sizeT ch, const sizeT chm)
        {
            if(this->chm != nullptr) return;
            this->chm = &(elrond::app().getChannelManager(chm));
            this->_ch = ch;
        }

        ELROND_INLINE_FUNC void TxChannel::trigger(const elrond::word data)
        {
            if(this->chm == nullptr) return;
            this->chm->txTrigger(this->ch, data);
        }
    }
}
