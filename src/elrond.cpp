#include "interface/Runtime.hpp"
#include "interface/Module.hpp"
#include "interface/ConfigMap.hpp"
#include "interface/DebugOut.hpp"

/*  ****************************************************************************
    *************************** elrond implementation **************************
    ****************************************************************************/

namespace elrond {

    ELROND_INLINE_FUNC interface::Runtime& app()
    { return *(ELROND_MOD_APP_VAR); }

    ELROND_INLINE_FUNC const interface::DebugOut& dout()
    { return elrond::app().dout(); }

    ELROND_INLINE_FUNC void error(const char* error)
    { app().onError(error); }

    #ifdef ELROND_WITH_STR_TYPE
        ELROND_INLINE_FUNC void error(elrond::String error)
        { app().onError(error); }
    #endif

}

/*  ****************************************************************************
    **************** elrond::interface::Module implementations *****************
    ****************************************************************************/
namespace elrond {
    namespace interface {
        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC Module::~Module(){}
        #endif
    }
}
