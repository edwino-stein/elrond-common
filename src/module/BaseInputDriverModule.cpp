#include "module/BaseInputDriverModule.hpp"

/*  ****************************************************************************
    *********** elrond::module::BaseInputDriverModule Implementation ***********
    ****************************************************************************/

namespace elrond {
    namespace module {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC BaseInputDriverModule::~BaseInputDriverModule(){}
        #endif

        ELROND_INLINE_FUNC elrond::ModuleType BaseInputDriverModule::getType() const
        { return elrond::ModuleType::INPUT; }
    }
}
