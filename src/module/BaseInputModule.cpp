#include "module/BaseInputModule.hpp"

/*  ****************************************************************************
    ************** elrond::module::BaseInputModule Implementation **************
    ****************************************************************************/

namespace elrond {
    namespace module {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC BaseInputModule::~BaseInputModule(){}
        #endif

        ELROND_INLINE_FUNC elrond::ModuleType BaseInputModule::getType() const
        { return elrond::ModuleType::INPUT; }
    }
}
