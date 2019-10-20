#if !defined  _ELROND_BASE_CHANNEL_MANAGER_HPP
#define _ELROND_BASE_CHANNEL_MANAGER_HPP

    #include "types.hpp"
    #include "runtime/channel/ProtocolHelper.hpp"

    namespace elrond {
        namespace channel {

            class BaseChannelManager {

                protected:
                    elrond::modules::BaseTransportModule &transport;

                public:

                    BaseChannelManager(elrond::modules::BaseTransportModule &transport);
            };
        }
    }

#endif
