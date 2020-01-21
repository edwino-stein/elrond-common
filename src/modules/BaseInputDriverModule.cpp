#include "modules/BaseInputDriverModule.hpp"
using namespace elrond::modules;

/*  ****************************************************************************
    ********* Implementation for elrond::modules::BaseInputDriverModule ********
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseInputDriverModule::~BaseInputDriverModule(){}
#endif

elrond::ModuleType BaseInputDriverModule::getType() const {
    return elrond::ModuleType::INPUT;
}
