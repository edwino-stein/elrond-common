#if !defined  _ELROND_BASE_CHANNEL_MANAGER_HPP
#define _ELROND_BASE_CHANNEL_MANAGER_HPP

    #include "elrond_ext_types.hpp"
    #include "elrond_protocol_helper.hpp"
    #include "channel/BufferWrapper.hpp"

    namespace elrond {
        namespace channel {

            class BaseChannelManager: public elrond::interface::ChannelManager {

                protected:

                    bool hasTxUpdate = false;
                    elrond::module::BaseDataLinkModule& dataLink;

                    virtual void init();
                    virtual void rxTrigger(const elrond::sizeT ch,
                                           const elrond::word data)=0;

                    virtual elrond::channel::BufferWrapper getTxBuffer() const =0;

                public:

                    BaseChannelManager(elrond::module::BaseDataLinkModule& dataLink);

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseChannelManager();
                    #endif

                    virtual void txTrigger(elrond::channel::TxChannel* const tx) override;

                    virtual void tryReceive(elrond::channel::OnChmReceiveHandleT handle,
                                            elrond::TaskContext* const ctx) override;

                    virtual bool txSync(const bool tryForce = false);

                    virtual elrond::sizeT getTotalTx() const =0;
                    virtual elrond::sizeT getTotalRx() const =0;

                    elrond::sizeT getRxBufferSize() const;
                    elrond::sizeT getTxBufferSize() const;
            };
        }
    }

#endif
