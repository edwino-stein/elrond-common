#ifndef ELROND_COMMON_STATIC_STRING_HPP
    #define ELROND_COMMON_STATIC_STRING_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        inline elrond::sizeT strLen(elrond::string str);
        inline char strAt(elrond::string str, elrond::sizeT pos);

        inline bool strEq(elrond::string str1, elrond::string str2);
        inline bool strEq(elrond::string str1, const char* str2);

        inline int strCmp(elrond::string str1, elrond::string str2);
        inline int strCmp(elrond::string str1, const char* str2);

        inline elrond::sizeT strCpy(elrond::string src, char des[], elrond::sizeT len);

        inline elrond::string nullstr();
    }

#endif
