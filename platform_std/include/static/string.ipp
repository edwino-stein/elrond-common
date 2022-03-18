
#ifndef ELROND_COMMON_STATIC_STRING_IPP
    #define ELROND_COMMON_STATIC_STRING_IPP

    #include "static/string.hpp"

    /*  **********************************************************************
        *************** Elrond string functions implementation ***************
        ********************************************************************** */

    namespace elrond
    {
        ELROND_INLINE elrond::sizeT strLen(elrond::string str)
        {
            return str.size();
        }
    }

#endif
