#if !defined  _ELROND_INTERFACE_MODULE_HPP
#define _ELROND_INTERFACE_MODULE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interface {

            class Module : public elrond::TaskContext {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Module();
                    #endif

                    virtual elrond::ModuleType getType() const =0;
                    virtual elrond::ModuleLoopControl& getLoopControl()=0;

                    virtual void onInit(elrond::interface::ConfigMap& cfg)=0;
                    virtual void onStart()=0;
                    virtual void onStop()=0;
                    virtual void loop()=0;

                    #ifdef ELROND_WITH_LINKED_NODES
                        Module* _nextNode = nullptr;
                    #endif
            };
        }
    }

#endif
