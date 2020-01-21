#if !defined  _ELROND_EXAMPLE_MODULE_HPP
    #define _ELROND_EXAMPLE_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"

    namespace elrond {
        namespace modules {

            class Example : public modules::BaseModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Example();
                    #endif

                    virtual void onInit(elrond::interface::ConfigMap& cfg) override;
                    virtual void onStart() override;
                    virtual void loop() override;
                    virtual void onStop() override;

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
