#ifndef ELROND_PLATFORM_STATIC_BITWISE_IPP
    #define ELROND_PLATFORM_STATIC_BITWISE_IPP

    #include "static/bitwise.hpp"

    /*  **********************************************************************
        *************** Elrond bitwise functions implementation **************
        ********************************************************************** */

    namespace elrond
    {
        ELROND_INLINE elrond::byte highByte(const elrond::word data)
        { return static_cast<elrond::byte>(data >> 8); }

        ELROND_INLINE elrond::byte lowByte(const elrond::word data)
        { return static_cast<elrond::byte>(data & 0x00FF); }

        ELROND_INLINE elrond::word makeWord
        (
            const elrond::byte high,
            const elrond::byte low
        ){ return static_cast<elrond::word>((high << 8) | (low & 0x00FF)); }

        ELROND_INLINE elrond::word highWord(const elrond::dWord data)
        { return static_cast<elrond::word>(data >> 16); }

        ELROND_INLINE elrond::word lowWord(const elrond::dWord data)
        { return static_cast<elrond::word>(data & 0x0000FFFF); }

        ELROND_INLINE elrond::dWord makeDWord
        (
            const elrond::word high,
            const elrond::word low
        ){
            return static_cast<elrond::dWord>
            (
                (static_cast<elrond::dWord>(high) << 16) | (low & 0x0000FFFF)
            );
        }

        ELROND_INLINE elrond::dWord makeDWord
        (
            const elrond::byte hwhb,
            const elrond::byte hwlb,
            const elrond::byte lwhb,
            const elrond::byte lwlb
        ){
            return elrond::makeDWord (
                elrond::makeWord(hwhb, hwlb),
                elrond::makeWord(lwhb, lwlb)
            );
        }

        ELROND_INLINE elrond::byte highByteHighWord(const elrond::dWord data)
        { return elrond::highByte(elrond::highWord(data)); }

        ELROND_INLINE elrond::byte lowByteHighWord(const elrond::dWord data)
        { return elrond::lowByte(elrond::highWord(data)); }

        ELROND_INLINE elrond::byte highByteLowWord(const elrond::dWord data)
        { return elrond::highByte(elrond::lowWord(data)); }

        ELROND_INLINE elrond::byte lowByteLowWord(const elrond::dWord data)
        { return elrond::lowByte(elrond::lowWord(data)); }
    }

#endif
