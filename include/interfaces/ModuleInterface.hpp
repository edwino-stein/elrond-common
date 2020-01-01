#if !defined  _ELROND_MODULE_INTERFACE_HPP
#define _ELROND_MODULE_INTERFACE_HPP

    #include "types.hpp"
    #include "runtime/TaskContext.hpp"

    namespace elrond {
        namespace interfaces {

            class ModuleInterface : public elrond::TaskContext {

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~ModuleInterface();
                    #endif

                    virtual elrond::ModuleType getType() const =0;
                    virtual elrond::ModuleLoopControl &getLoopControl() =0;

                    virtual void onInit(elrond::interfaces::ConfigMapInterface &cfg)=0;
                    virtual void onStart()=0;
                    virtual void onStop()=0;
                    virtual void loop()=0;

                    #if defined USE_LINKED_NODES
                        ModuleInterface *_nextNode = nullptr;
                    #endif
            };
        }
    }

#endif
