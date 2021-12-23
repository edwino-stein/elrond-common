#include "module/BaseModule.hpp"
#include "interface/Runtime.hpp"
#include "interface/ConfigMap.hpp"

/*  ****************************************************************************
    **************** elrond::module::BaseModule Implementation *****************
    ****************************************************************************/

namespace elrond {
    namespace module {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC BaseModule::~BaseModule(){}
        #endif

        ELROND_INLINE_FUNC void BaseModule::onInit(
            elrond::interface::ConfigMap& cfg,
            elrond::LoopControl& lc
        ){}

        ELROND_INLINE_FUNC void BaseModule::onStart(){}
        ELROND_INLINE_FUNC void BaseModule::loop(){}
        ELROND_INLINE_FUNC void BaseModule::onStop(){}

        ELROND_INLINE_FUNC elrond::ModuleType BaseModule::getType() const
        { return elrond::ModuleType::GENERIC; }
    }
}
