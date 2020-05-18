#if !defined  _ELROND_TX_CHANNEL_HPP
#define _ELROND_TX_CHANNEL_HPP

    #include "elrond_types.hpp"
    #include "channel/BaseChannel.hpp"

    namespace elrond {
        namespace channel {

            class TxChannel : public elrond::channel::BaseChannel {

                protected:

                    elrond::interface::ChannelManager* chm = nullptr;

                public:

                    void init(const elrond::uInt8 ch, const sizeT chm);
                    void trigger(const elrond::word data);
            };
        }
    }

#endif
