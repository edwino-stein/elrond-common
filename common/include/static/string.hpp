#ifndef ELROND_COMMON_STATIC_STRING_HPP
    #define ELROND_COMMON_STATIC_STRING_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        elrond::sizeT strLen(elrond::string str);
        char strAt(elrond::string str, const elrond::sizeT pos);

        bool strEq(elrond::string str1, elrond::string str2);
        bool strEq(elrond::string str1, const char*  str2);

        int strCmp(elrond::string str1, elrond::string str2);
        int strCmp(elrond::string str1, const char*  str2);

        elrond::sizeT
        strCpy(elrond::string src, char des[], const elrond::sizeT len);
    }

#endif
