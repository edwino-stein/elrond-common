#include "modules/BaseTransportModule.hpp"
using namespace elrond::modules;

/*  ****************************************************************************
    ********** Implementation for elrond::modules::BaseTransportModule *********
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    BaseTransportModule::~BaseTransportModule(){}
#endif

elrond::ModuleType BaseTransportModule::getType() const {
    return elrond::ModuleType::TRANSPORT;
}
