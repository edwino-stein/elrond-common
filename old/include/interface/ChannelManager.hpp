#if !defined  _ELROND_INTERFACE_CHANNEL_MANAGER_HPP
#define _ELROND_INTERFACE_CHANNEL_MANAGER_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace interface {

            class ChannelManager {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~ChannelManager();
                    #endif

                    virtual void txTrigger(elrond::channel::TxChannel* const tx)=0;
                    virtual void addRxListener(elrond::channel::RxChannel* const rx)=0;

                    virtual void tryReceive(elrond::channel::OnChmReceiveHandleT handle,
                                            elrond::TaskContext* const ctx)=0;
            };
        }
    }

#endif
