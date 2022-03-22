#ifndef ELROND_COMMON_MODULE_ABSTRACT_IPP
    #define ELROND_COMMON_MODULE_ABSTRACT_IPP

    #include "module/Abstract.hpp"

    namespace elrond
    {
        namespace module
        {
            ELROND_INLINE void Abstract::setup(const elrond::Arguments&) {}
            ELROND_INLINE void Abstract::start() {}
            ELROND_INLINE void Abstract::loop() {}
            ELROND_INLINE void Abstract::stop() {}
        }
    }

#endif
