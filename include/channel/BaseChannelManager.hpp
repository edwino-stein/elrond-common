#if !defined  _ELROND_BASE_CHANNEL_MANAGER_HPP
#define _ELROND_BASE_CHANNEL_MANAGER_HPP

    #include "types.hpp"
    #include "elrond_protocol_helper.hpp"

    namespace elrond {
        namespace channel {

            class BaseChannelManager {

                protected:
                    elrond::module::BaseTransportModule &transport;
                    bool hasTxUpdate = false;

                    virtual void rxTrigger(const elrond::sizeT ch, const elrond::word data)=0;
                    virtual elrond::byte *getTxBuffer() const =0;

                public:

                    BaseChannelManager(elrond::module::BaseTransportModule &transport);

                    virtual void init();
                    virtual void txTrigger(const elrond::sizeT ch, elrond::word data);
                    virtual bool txSync(const bool force = false);

                    virtual void onReceive(elrond::byte data[], const elrond::sizeT length);
                    virtual void addRxListener(const elrond::sizeT ch, elrond::channel::RxChannel *rx)=0;

                    virtual elrond::sizeT getTotalTx() const =0;
                    virtual elrond::sizeT getTotalRx() const =0;

                    virtual elrond::sizeT getRxBufferSize() const;
                    virtual elrond::sizeT getTxBufferSize() const;

                    #ifdef ELROND_WITH_LINKED_NODES
                        BaseChannelManager *_nextNode = nullptr;
                    #endif
            };
        }
    }

#endif
