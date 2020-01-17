#if !defined  _ELROND_RX_CHANNEL_HPP
#define _ELROND_RX_CHANNEL_HPP

    #include "types.hpp"

    namespace elrond {
        namespace channel {
            class RxChannel {

                protected:
                    elrond::word _data;
                    elrond::channel::OnReceiveHandleT handle;
                    elrond::TaskContext* ctx = nullptr;

                public:

                    elrond::word const& data;
                    RxChannel();

                    void init(
                        const elrond::sizeT chId,
                        const elrond::sizeT chm,
                        elrond::channel::OnReceiveHandleT handle,
                        elrond::TaskContext* const ctx = nullptr
                    );

                    void trigger(const elrond::word data);

                    #ifdef ELROND_WITH_LINKED_NODES
                        RxChannel *_nextNode = nullptr;
                    #endif
            };
        }
    }

#endif
