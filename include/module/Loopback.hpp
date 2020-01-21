#if !defined  _ELROND_LOOPBACK_MODULE_HPP
    #define _ELROND_LOOPBACK_MODULE_HPP

    #include "module/BaseTransportModule.hpp"

    namespace elrond {
        namespace module {

            class Loopback : public elrond::module::BaseTransportModule {

                protected:
                    elrond::channel::BaseChannelManager *cm = nullptr;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Loopback();
                    #endif

                    void onInit(elrond::interface::ConfigMap& cfg) override;
                    void send(elrond::byte data[], const elrond::sizeT length) override;
                    void setChannelManager(elrond::channel::BaseChannelManager* cm) override;

                    #ifdef ELROND_WITH_MODULES_INFO
                        static const char *_getInternalName();
                        static const char *_infoMainClassName();
                        static int _infoApiVersion();
                        static int _infoApiRevision();
                        static const char *_infoPrettyName();
                        static const char *_infoAuthorName();
                        static const char *_infoAuthorEmail();
                        static const char *_infoVersion();
                    #endif
            };
        }
    }

#endif
