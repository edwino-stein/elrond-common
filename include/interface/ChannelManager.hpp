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

                    virtual void txTrigger(const elrond::sizeT ch,
                                           const elrond::word data)=0;

                    virtual void onReceive(elrond::byte data[],
                                           const elrond::sizeT length)=0;

                    virtual void addRxListener(const elrond::sizeT ch,
                                               elrond::channel::RxChannel* rx)=0;

                    virtual elrond::sizeT getTotalTx() const =0;
                    virtual elrond::sizeT getTotalRx() const =0;

                    virtual elrond::sizeT getRxBufferSize() const =0;
                    virtual elrond::sizeT getTxBufferSize() const =0;
            };
        }
    }

#endif
