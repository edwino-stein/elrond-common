#if !defined  _ELROND_TX_CHANNEL_HPP
#define _ELROND_TX_CHANNEL_HPP

    #include "types.hpp"

    namespace elrond {
        namespace channel {
            class TxChannel {

                protected:
                    elrond::sizeT chId = 0;
                    elrond::channel::BaseChannelManager *chm = nullptr;

                public:
                    void init(const elrond::sizeT chId, const sizeT chm);
                    void trigger(const elrond::word data);
            };
        }
    }

#endif
