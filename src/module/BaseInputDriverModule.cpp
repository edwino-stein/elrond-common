#include "module/BaseInputDriverModule.hpp"

using elrond::module::BaseInputDriverModule;

/*  ****************************************************************************
    *********** elrond::module::BaseInputDriverModule Implementation ***********
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseInputDriverModule::~BaseInputDriverModule(){}
#endif

elrond::ModuleType BaseInputDriverModule::getType() const
{
    return elrond::ModuleType::INPUT;
}
