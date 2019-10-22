#if !defined  _ELROND_BITWISE_HPP
#define _ELROND_BITWISE_HPP

    #include "types.hpp"

    namespace elrond {

        elrond::byte highByte(const elrond::word data);
        elrond::byte lowByte(const elrond::word data);
        elrond::word makeWord(const elrond::byte high, const elrond::byte low);

        elrond::word highWord(const elrond::dword data);
        elrond::word lowWord(const elrond::dword data);
        elrond::dword makeDWord(const elrond::word high, elrond::word low);
    }

#endif