#include "modules/BaseGpioModule.hpp"
using namespace elrond::modules;

/*  ****************************************************************************
    ************ Implementation for elrond::modules::BaseGpioModule ************
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    BaseGpioModule::~BaseGpioModule(){}
#endif

elrond::ModuleType BaseGpioModule::getType() const {
    return elrond::ModuleType::GPIO;
}
