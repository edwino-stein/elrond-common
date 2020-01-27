#include "module/BaseTransportModule.hpp"

/*  ****************************************************************************
    ************ elrond::module::BaseTransportModule Implementation ************
    ****************************************************************************/

namespace elrond {
    namespace module {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC BaseTransportModule::~BaseTransportModule(){}
        #endif

        ELROND_INLINE_FUNC elrond::ModuleType BaseTransportModule::getType() const
        { return elrond::ModuleType::TRANSPORT; }
    }
}
