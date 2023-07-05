#ifndef ELROND_COMMON_STATIC_BITWISE_HPP
    #define ELROND_COMMON_STATIC_BITWISE_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        inline elrond::byte highByte(elrond::word data);
        inline elrond::byte lowByte(elrond::word data);
        inline elrond::word makeWord(elrond::byte high, elrond::byte low);

        inline elrond::word highWord(elrond::dWord data);
        inline elrond::word lowWord(elrond::dWord data);
        inline elrond::dWord makeDWord(elrond::word high, elrond::word low);

        inline elrond::dWord makeDWord( elrond::byte hwhb,
                                        elrond::byte hwlb,
                                        elrond::byte lwhb,
                                        elrond::byte lwlb);

        inline elrond::byte highByteHighWord(elrond::dWord data);
        inline elrond::byte lowByteHighWord(elrond::dWord data);
        inline elrond::byte highByteLowWord(elrond::dWord data);
        inline elrond::byte lowByteLowWord(elrond::dWord data);
    }

#endif
