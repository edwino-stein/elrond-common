#include "interfaces.hpp"
using namespace elrond::interfaces;

/*  ****************************************************************************
    ********* Implementations for elrond::interfaces::ModuleInterface **********
    ****************************************************************************/
#if !defined WITHOUT_DESTRUCTORS
    ModuleInterface::~ModuleInterface(){}
#endif

/*  ****************************************************************************
    ************************* Implementations for elrond ***********************
    ****************************************************************************/
RuntimeInterface &elrond::app(){return *(elrond::__rtInstance__);}
const DebugOutInterface &elrond::dout(){ return elrond::app().dout(); }
void elrond::error(const char *error){ elrond::app().onError(error); }

#if defined INO_PLATFORM
    void elrond::error(const __FlashStringHelper *error){ elrond::app().onError(error); }
#endif
