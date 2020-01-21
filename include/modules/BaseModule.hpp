#if !defined  _ELROND_BASE_MODULE_HPP
    #define _ELROND_BASE_MODULE_HPP

    #include "types.hpp"
    #include "interfaces/ModuleInterface.hpp"

    namespace elrond {
        namespace modules {

            class BaseModule : public interfaces::ModuleInterface {

                protected:
                    elrond::ModuleLoopControl _loopControl;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseModule();
                    #endif

                    virtual elrond::ModuleType getType() const override;
                    virtual elrond::ModuleLoopControl &getLoopControl() override;

                    virtual void onInit(elrond::interfaces::ConfigMapInterface &cfg) override;
                    virtual void onStart() override;
                    virtual void loop() override;
                    virtual void onStop() override;
            };
        }
    }

#endif
