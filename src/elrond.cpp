#include "interface/Runtime.hpp"
#include "interface/Module.hpp"
#include "interface/ConfigMap.hpp"
#include "interface/DebugOut.hpp"

using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::DebugOut;

/*  ****************************************************************************
    **************** elrond::interface::Module implementations *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    Module::~Module(){}
#endif

/*  ****************************************************************************
    *************************** elrond implementation **************************
    ****************************************************************************/

Runtime& elrond::app(){return *(elrond::__rtInstance__);}
const DebugOut& elrond::dout(){ return elrond::app().dout(); }
void elrond::error(const char* error){ elrond::app().onError(error); }
#ifdef ELROND_WITH_STR_TYPE
    void elrond::error(elrond::String error){ elrond::app().onError(error); }
#endif
