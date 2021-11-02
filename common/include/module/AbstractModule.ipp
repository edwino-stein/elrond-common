#ifndef ELROND_COMMON_MODULE_ABSTRACT_MODULE_IPP
    #define ELROND_COMMON_MODULE_ABSTRACT_MODULE_IPP

    #include "module/AbstractModule.hpp"

    namespace elrond
    {
        namespace module
        {
            #ifndef ELROND_DISABLE_DESTRUCTORS
                ELROND_INLINE AbstractModule::~AbstractModule(){}
            #endif

            ELROND_INLINE void AbstractModule::setup(){}
            ELROND_INLINE void AbstractModule::start() {}
            ELROND_INLINE void AbstractModule::loop() {}
            ELROND_INLINE void AbstractModule::stop() {}
        }
    }

#endif
