#include "runtime/bitwise.hpp"

/*  ****************************************************************************
    ****************** Elrond bitwise functions implementation *****************
    ****************************************************************************/

elrond::byte elrond::highByte(const elrond::word data)
{ return (elrond::byte) (data >> 8); }

elrond::byte elrond::lowByte(const elrond::word data)
{ return (elrond::byte) (data & 0x00FF); }

elrond::word elrond::makeWord(const elrond::byte high, const elrond::byte low)
{ return (elrond::word) ((high << 8) | (low & 0x00FF)); }

elrond::word elrond::highWord(const elrond::dWord data)
{ return (elrond::word) (data >> 16); }

elrond::word elrond::lowWord(const elrond::dWord data)
{ return (elrond::word) (data & 0x0000FFFF); }

elrond::dWord elrond::makeDWord(const elrond::word high, elrond::word low)
{ return (elrond::dWord) ((((elrond::dWord) high) << 16) | (low & 0x0000FFFF)); }