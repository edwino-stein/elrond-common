#include "channel/TxChannel.hpp"
#include "channel/BaseChannelManager.hpp"
#include "interface/Runtime.hpp"

/*  ****************************************************************************
    **************** elrond::channel::TxChannel Implementation *****************
    ****************************************************************************/

namespace elrond {
    namespace channel {

        ELROND_INLINE_FUNC void TxChannel::init(const elrond::sizeT chId, const sizeT chm)
        {
            this->chm = &(elrond::app().getChannelManager(chm));
            this->chId = chId;
        }

        ELROND_INLINE_FUNC void TxChannel::trigger(const elrond::word data)
        {
            if(this->chm == nullptr) return;
            this->chm->txTrigger(this->chId, data);
        }
    }
}
