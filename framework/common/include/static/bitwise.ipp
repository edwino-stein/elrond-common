#ifndef ELROND_PLATFORM_STATIC_BITWISE_IPP
    #define ELROND_PLATFORM_STATIC_BITWISE_IPP

    #include "static/bitwise.hpp"

    /*  **********************************************************************
        *************** Elrond bitwise functions implementation **************
        ********************************************************************** */

    namespace elrond
    {
        inline elrond::byte highByte(elrond::word data)
        { return static_cast<elrond::byte>(data >> 8); }

        inline elrond::byte lowByte(elrond::word data)
        { return static_cast<elrond::byte>(data & 0x00FF); }

        inline elrond::word makeWord(elrond::byte high, const elrond::byte low)
        { return static_cast<elrond::word>((high << 8) | (low & 0x00FF)); }

        inline elrond::word highWord(elrond::dWord data)
        { return static_cast<elrond::word>(data >> 16); }

        inline elrond::word lowWord(elrond::dWord data)
        { return static_cast<elrond::word>(data & 0x0000FFFF); }

        inline elrond::dWord makeDWord(elrond::word high, elrond::word low)
        {
            return static_cast<elrond::dWord>
            (
                (static_cast<elrond::dWord>(high) << 16) | (low & 0x0000FFFF)
            );
        }

        inline elrond::dWord makeDWord( elrond::byte hwhb,
                                        elrond::byte hwlb,
                                        elrond::byte lwhb,
                                        elrond::byte lwlb)
        {
            return elrond::makeDWord (
                elrond::makeWord(hwhb, hwlb),
                elrond::makeWord(lwhb, lwlb)
            );
        }

        inline elrond::byte highByteHighWord(elrond::dWord data)
        { return elrond::highByte(elrond::highWord(data)); }

        inline elrond::byte lowByteHighWord(elrond::dWord data)
        { return elrond::lowByte(elrond::highWord(data)); }

        inline elrond::byte highByteLowWord(elrond::dWord data)
        { return elrond::highByte(elrond::lowWord(data)); }

        inline elrond::byte lowByteLowWord(elrond::dWord data)
        { return elrond::lowByte(elrond::lowWord(data)); }
    }

#endif
