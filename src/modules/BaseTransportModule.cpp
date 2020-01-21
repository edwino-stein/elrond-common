#include "modules/BaseTransportModule.hpp"
using namespace elrond::modules;

/*  ****************************************************************************
    ********** Implementation for elrond::modules::BaseTransportModule *********
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    BaseTransportModule::~BaseTransportModule(){}
#endif

elrond::ModuleType BaseTransportModule::getType() const {
    return elrond::ModuleType::TRANSPORT;
}
