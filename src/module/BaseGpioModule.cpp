#include "module/BaseGpioModule.hpp"

using elrond::module::BaseGpioModule;

/*  ****************************************************************************
    ************** elrond::module::BaseGpioModule Implementation ***************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseGpioModule::~BaseGpioModule(){}
#endif

elrond::ModuleType BaseGpioModule::getType() const
{
    return elrond::ModuleType::GPIO;
}
