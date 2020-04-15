#if !defined  _ELROND_TX_CHANNEL_HPP
#define _ELROND_TX_CHANNEL_HPP

    #include "types.hpp"
    #include "interface/Channel.hpp"

    namespace elrond {
        namespace channel {

            class TxChannel : public elrond::interface::Channel {

                protected:

                    elrond::interface::ChannelManager* chm = nullptr;

                public:

                    TxChannel();

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~TxChannel();
                    #endif

                    void init(const elrond::sizeT ch, const sizeT chm);
                    void trigger(const elrond::word data);
            };
        }
    }

#endif
