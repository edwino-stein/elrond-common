#include "interfaces.hpp"
using namespace elrond::interfaces;

/*  ****************************************************************************
    ************************* Implementations for elrond ***********************
    ****************************************************************************/
RuntimeInterface &elrond::app(){return *(elrond::__rtInstance__);}
void elrond::error(const char *error){ elrond::app().onError(error); }
