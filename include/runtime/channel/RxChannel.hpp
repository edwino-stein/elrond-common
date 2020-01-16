#if !defined  _ELROND_RX_CHANNEL_HPP
#define _ELROND_RX_CHANNEL_HPP

    #include "types.hpp"

    namespace elrond {
        namespace channel {
            class RxChannel {

                protected:
                    elrond::word _data;
                    elrond::channel::onReceiveT handle;
                    elrond::TaskContext *ctx = nullptr;

                public:

                    elrond::word const &data;
                    RxChannel();
                    void init(const elrond::sizeT chId, const elrond::sizeT chm, elrond::channel::onReceiveT handle, elrond::TaskContext *ctx = nullptr);
                    void trigger(const elrond::word data);

                    #if defined USE_LINKED_NODES
                        RxChannel *_nextNode = nullptr;
                    #endif
            };
        }
    }

#endif
