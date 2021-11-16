#ifndef ELROND_COMMON_INTERFACE_CONTEXT_HPP
    #define ELROND_COMMON_INTERFACE_CONTEXT_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Context
            {
                public:
                    virtual ~Context() = ELROND_DEFAULT_DESTRUCTOR;
            };
        }
    }

#endif
