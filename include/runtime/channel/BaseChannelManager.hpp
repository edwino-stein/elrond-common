#if !defined  _ELROND_BASE_CHANNEL_MANAGER_HPP
#define _ELROND_BASE_CHANNEL_MANAGER_HPP

    #include "types.hpp"
    #include "runtime/channel/ProtocolHelper.hpp"

    namespace elrond {
        namespace channel {

            class BaseChannelManager {

                protected:
                    elrond::modules::BaseTransportModule &transport;

                    virtual elrond::byte *getTxBuffer() const =0;

                public:

                    BaseChannelManager(elrond::modules::BaseTransportModule &transport);

                    virtual void init();
                    virtual void txTrigger(const elrond::sizeT ch, elrond::word data);
                    virtual void onSend();
                    virtual elrond::sizeT getTotalTx() const =0;

                    virtual elrond::sizeT getTxBufferSize() const;

            };
        }
    }

#endif
