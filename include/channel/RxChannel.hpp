#if !defined  _ELROND_RX_CHANNEL_HPP
#define _ELROND_RX_CHANNEL_HPP

    #include "elrond_types.hpp"
    #include "interface/Channel.hpp"

    namespace elrond {
        namespace channel {

            class RxChannel : public elrond::interface::Channel {

                protected:

                    elrond::channel::OnReceiveHandleT handle = nullptr;
                    elrond::TaskContext* ctx = nullptr;

                public:

                    RxChannel();

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~RxChannel();
                    #endif

                    void init(
                        const elrond::sizeT ch,
                        const elrond::sizeT chm,
                        elrond::channel::OnReceiveHandleT handle,
                        elrond::TaskContext* const ctx = nullptr
                    );

                    void trigger(const elrond::word data);
            };
        }
    }

#endif
