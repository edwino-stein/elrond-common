#if !defined  _ELROND_LOOPBACK_TRANSPORT_MODULE_HPP
    #define _ELROND_LOOPBACK_TRANSPORT_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseTransportModule.hpp"

    namespace elrond {
        namespace modules {

            class LoopbackTransportModule : public modules::BaseTransportModule {

                protected:
                    elrond::channel::BaseChannelManager *cm = nullptr;

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~LoopbackTransportModule();
                    #endif

                    void onInit(elrond::config::ConfigMap &cfg) override;
                    void send(elrond::byte data[], const elrond::sizeT length) override;
                    void setChannelManager(elrond::channel::BaseChannelManager *cm) override;

                    static const char *_getInternalName();
                    static const char *_infoMainClassName();
                    static int _infoApiVersion();
                    static int _infoApiRevision();
                    static const char *_infoPrettyName();
                    static const char *_infoAuthorName();
                    static const char *_infoAuthorEmail();
                    static const char *_infoVersion();
            };
        }
    }

#endif
