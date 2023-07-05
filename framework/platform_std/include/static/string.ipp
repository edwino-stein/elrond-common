
#ifndef ELROND_COMMON_STATIC_STRING_IPP
    #define ELROND_COMMON_STATIC_STRING_IPP

    #include "static/string.hpp"

    /*  **********************************************************************
        *************** Elrond string functions implementation ***************
        ********************************************************************** */

    namespace elrond
    {
        inline elrond::sizeT strLen(elrond::string str)
        { return str.size(); }

        inline char strAt(elrond::string str, elrond::sizeT pos)
        { return pos <= str.length() ? str[pos] : '\0'; }

        inline bool strEq(elrond::string str1, elrond::string str2)
        { return str1 == str2; }

        inline bool strEq(elrond::string str1, const char* str2)
        { return str1 == str2; }

        inline int strCmp(elrond::string str1, elrond::string str2)
        { return str1.compare(str2); }

        inline int strCmp(elrond::string str1, const char* str2)
        { return str1.compare(str2); }

        inline elrond::sizeT strCpy(elrond::string src, char des[], elrond::sizeT len)
        {
            auto l = src.copy(des, len);
            if(l == len) l -= 1;
            des[l] = '\0';
            return l;
        }

        inline elrond::string nullstr() { return std::string(); }
    }

#endif
