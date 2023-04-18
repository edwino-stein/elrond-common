#ifndef ELROND_COMMON_STATIC_BITWISE_HPP
    #define ELROND_COMMON_STATIC_BITWISE_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        elrond::byte highByte(const elrond::word data);
        elrond::byte lowByte(const elrond::word data);
        elrond::word makeWord(const elrond::byte high, const elrond::byte low);

        elrond::word highWord(const elrond::dWord data);
        elrond::word lowWord(const elrond::dWord data);
        elrond::dWord makeDWord(const elrond::word high, const elrond::word low);

        elrond::dWord makeDWord(const elrond::byte hwhb,
                                const elrond::byte hwlb,
                                const elrond::byte lwhb,
                                const elrond::byte lwlb);

        elrond::byte highByteHighWord(const elrond::dWord data);
        elrond::byte lowByteHighWord(const elrond::dWord data);
        elrond::byte highByteLowWord(const elrond::dWord data);
        elrond::byte lowByteLowWord(const elrond::dWord data);
    }

#endif
