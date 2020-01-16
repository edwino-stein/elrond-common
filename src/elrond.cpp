#include "interfaces.hpp"

using elrond::interfaces::ModuleInterface;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::DebugOutInterface;

/*  ****************************************************************************
    ************ elrond::interfaces::ModuleInterface implementations ***********
    ****************************************************************************/

#if !defined WITHOUT_DESTRUCTORS
    ModuleInterface::~ModuleInterface(){}
#endif

/*  ****************************************************************************
    *************************** elrond implementation **************************
    ****************************************************************************/

RuntimeInterface& elrond::app(){return *(elrond::__rtInstance__);}
const DebugOutInterface& elrond::dout(){ return elrond::app().dout(); }
void elrond::error(const char* error){ elrond::app().onError(error); }
#ifdef ELROND_WITH_STR_TYPE
    void elrond::error(elrond::String error){ elrond::app().onError(error); }
#endif
