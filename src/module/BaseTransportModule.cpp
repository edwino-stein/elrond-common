#include "module/BaseTransportModule.hpp"

using elrond::module::BaseTransportModule;

/*  ****************************************************************************
    ************ elrond::module::BaseTransportModule Implementation ************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseTransportModule::~BaseTransportModule(){}
#endif

elrond::ModuleType BaseTransportModule::getType() const
{
    return elrond::ModuleType::TRANSPORT;
}
