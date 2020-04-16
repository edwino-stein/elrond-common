#if !defined  _ELROND_BITWISE_HPP
#define _ELROND_BITWISE_HPP

    #include "elrond_types.hpp"

    namespace elrond {

        elrond::byte highByte(const elrond::word data);
        elrond::byte lowByte(const elrond::word data);
        elrond::word makeWord(const elrond::byte high, const elrond::byte low);

        elrond::word highWord(const elrond::dWord data);
        elrond::word lowWord(const elrond::dWord data);
        elrond::dWord makeDWord(const elrond::word high, const elrond::word low);
    }

#endif
