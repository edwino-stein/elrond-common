#ifndef ELROND_COMMON_MODULE_ABSTRACT_IPP
    #define ELROND_COMMON_MODULE_ABSTRACT_IPP

    #include "module/Abstract.hpp"

    namespace elrond
    {
        namespace module
        {
            ELROND_INLINE void Abstract::setup(elrond::ContextP) {}
            ELROND_INLINE void Abstract::start(elrond::ContextP) {}
            ELROND_INLINE void Abstract::loop(elrond::ContextP) {}
            ELROND_INLINE void Abstract::stop(elrond::ContextP) {}
        }
    }

#endif
