#if !defined  _ELROND_MODULE_INTERFACE_HPP
#define _ELROND_MODULE_INTERFACE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interfaces {

            class ModuleInterface {

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~ModuleInterface();
                    #endif

                    virtual elrond::ModuleType getType() const =0;
            };
        }
    }

#endif
