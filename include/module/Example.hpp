#if !defined  _ELROND_EXAMPLE_MODULE_HPP
    #define _ELROND_EXAMPLE_MODULE_HPP

    #include "module/BaseModule.hpp"

    namespace elrond {
        namespace module {

            class Example : public elrond::module::BaseModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Example();
                    #endif

                    virtual void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;
                    virtual void onStart() override;
                    virtual void loop() override;
                    virtual void onStop() override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
