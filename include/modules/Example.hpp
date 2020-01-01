#if !defined  _ELROND_EXAMPLE_MODULE_HPP
    #define _ELROND_EXAMPLE_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"

    namespace elrond {
        namespace modules {

            class Example : public modules::BaseModule {

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~Example();
                    #endif

                    virtual void onInit(elrond::interfaces::ConfigMapInterface &cfg) override;
                    virtual void onStart() override;
                    virtual void loop() override;
                    virtual void onStop() override;

                    #if defined GENERIC_STD_PLATFORM
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
