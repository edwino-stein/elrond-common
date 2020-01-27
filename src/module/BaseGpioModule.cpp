#include "module/BaseGpioModule.hpp"

/*  ****************************************************************************
    ************** elrond::module::BaseGpioModule Implementation ***************
    ****************************************************************************/

namespace elrond {
    namespace module {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC BaseGpioModule::~BaseGpioModule(){}
        #endif

        ELROND_INLINE_FUNC elrond::ModuleType BaseGpioModule::getType() const
        { return elrond::ModuleType::GPIO; }
    }
}
