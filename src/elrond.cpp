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
void elrond::error(const char *error){ elrond::app().onError(error); }
