
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

        ELROND_INLINE char strAt(elrond::string str, const elrond::sizeT pos)
        {
            return str[pos];
        }

        ELROND_INLINE bool strEq(elrond::string str1, elrond::string str2)
        {
            return str1 == str2;
        }

        ELROND_INLINE bool strEq(elrond::string str1, const char*  str2)
        {
            return str1 == str2;
        }

        ELROND_INLINE int strCmp(elrond::string str1, elrond::string str2)
        {
            return str1.compare(str2);
        }

        ELROND_INLINE int strCmp(elrond::string str1, const char*  str2)
        {
            return str1.compare(str2);
        }
    }

#endif
