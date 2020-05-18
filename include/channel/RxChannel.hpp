#if !defined  _ELROND_RX_CHANNEL_HPP
#define _ELROND_RX_CHANNEL_HPP

    #include "elrond_types.hpp"
    #include "channel/BaseChannel.hpp"

    namespace elrond {
        namespace channel {

            class RxChannel : public elrond::channel::BaseChannel {

                protected:

                    elrond::channel::OnReceiveHandleT handle = nullptr;
                    elrond::TaskContext* ctx = nullptr;

                public:

                    void init(
                        const elrond::uInt8 ch,
                        const elrond::sizeT chm,
                        elrond::channel::OnReceiveHandleT handle,
                        elrond::TaskContext* const ctx = nullptr
                    );

                    void trigger(const elrond::word data);
            };
        }
    }

#endif
