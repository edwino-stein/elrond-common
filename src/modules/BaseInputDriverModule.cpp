#include "modules/BaseInputDriverModule.hpp"
using namespace elrond::modules;

/*  ****************************************************************************
    ********* Implementation for elrond::modules::BaseInputDriverModule ********
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    BaseInputDriverModule::~BaseInputDriverModule(){}
#endif

elrond::ModuleType BaseInputDriverModule::getType() const {
    return elrond::ModuleType::INPUT;
}
