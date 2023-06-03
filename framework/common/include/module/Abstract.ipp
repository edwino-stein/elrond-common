#ifndef ELROND_COMMON_MODULE_ABSTRACT_IPP
    #define ELROND_COMMON_MODULE_ABSTRACT_IPP

    #include "module/Abstract.hpp"

    namespace elrond
    {
        namespace module
        {
            ELROND_INLINE void Abstract::setup(elrond::Context) {}
            ELROND_INLINE void Abstract::start(elrond::Context) {}
            ELROND_INLINE void Abstract::loop(elrond::Context) {}
            ELROND_INLINE void Abstract::stop(elrond::Context) {}
        }
    }

#endif
