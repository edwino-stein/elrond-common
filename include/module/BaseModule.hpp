#if !defined  _ELROND_BASE_MODULE_HPP
    #define _ELROND_BASE_MODULE_HPP

    #include "interface/Module.hpp"

    namespace elrond {
        namespace module {

            class BaseModule : public elrond::interface::Module {

                protected:

                    elrond::ModuleLoopControl _loopControl;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseModule();
                    #endif

                    virtual elrond::ModuleType getType() const override;
                    virtual void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;
                    virtual void onStart() override;
                    virtual void loop() override;
                    virtual void onStop() override;
            };
        }
    }

#endif
