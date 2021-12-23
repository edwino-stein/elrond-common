#include "channel/BaseChannel.hpp"

/*  ****************************************************************************
    *************** elrond::channel::BaseChannel Implementation ****************
    ****************************************************************************/

namespace elrond {
    namespace channel {

        ELROND_INLINE_FUNC elrond::uInt16 BaseChannel::ch() const
        { return this->_ch; }

        ELROND_INLINE_FUNC elrond::word BaseChannel::data() const
        {return this->_data; }
    }
}
