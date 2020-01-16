#include "modules/BaseGpioModule.hpp"
using namespace elrond::modules;

/*  ****************************************************************************
    ************ Implementation for elrond::modules::BaseGpioModule ************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseGpioModule::~BaseGpioModule(){}
#endif

elrond::ModuleType BaseGpioModule::getType() const {
    return elrond::ModuleType::GPIO;
}
