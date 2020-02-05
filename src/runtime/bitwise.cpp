#include "runtime/bitwise.hpp"

/*  ****************************************************************************
    ****************** Elrond bitwise functions implementation *****************
    ****************************************************************************/

namespace elrond {

    ELROND_INLINE_FUNC elrond::byte highByte(const elrond::word data)
    { return (elrond::byte) (data >> 8); }

    ELROND_INLINE_FUNC elrond::byte lowByte(const elrond::word data)
    { return (elrond::byte) (data & 0x00FF); }

    ELROND_INLINE_FUNC elrond::word makeWord(
        const elrond::byte high,
        const elrond::byte low
    ){ return (elrond::word) ((high << 8) | (low & 0x00FF)); }

    ELROND_INLINE_FUNC elrond::word highWord(const elrond::dWord data)
    { return (elrond::word) (data >> 16); }

    ELROND_INLINE_FUNC elrond::word lowWord(const elrond::dWord data)
    { return (elrond::word) (data & 0x0000FFFF); }

    ELROND_INLINE_FUNC elrond::dWord makeDWord(
        const elrond::word high,
        const elrond::word low
    ){ return (elrond::dWord) ((((elrond::dWord) high) << 16) | (low & 0x0000FFFF)); }

}
