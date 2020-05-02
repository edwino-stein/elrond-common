#if !defined  _ELROND_BASE_CHANNEL_MANAGER_HPP
#define _ELROND_BASE_CHANNEL_MANAGER_HPP

    #include "elrond_ext_types.hpp"
    #include "interface/ChannelManager.hpp"
    #include "elrond_protocol_helper.hpp"

    namespace elrond {
        namespace channel {

            class BaseChannelManager: public elrond::interface::ChannelManager {

                protected:

                    elrond::module::BaseTransportModule& transport;
                    bool hasTxUpdate = false;

                    virtual elrond::byte* getTxBuffer() const =0;
                    virtual void rxTrigger(const elrond::sizeT ch,
                                           const elrond::word data)=0;

                    virtual void init();

                public:

                    BaseChannelManager(elrond::module::BaseTransportModule& transport);

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseChannelManager();
                    #endif

                    virtual bool txSync(const bool force = false);

                    virtual void txTrigger(const elrond::sizeT ch,
                                           const elrond::word data) override;

                    virtual void onReceive(elrond::byte data[],
                                           const elrond::sizeT length) override;

                    virtual elrond::sizeT getRxBufferSize() const override;
                    virtual elrond::sizeT getTxBufferSize() const override;

                    #ifdef ELROND_WITH_LINKED_NODES
                        BaseChannelManager *_nextNode = nullptr;
                    #endif
            };
        }
    }

#endif
