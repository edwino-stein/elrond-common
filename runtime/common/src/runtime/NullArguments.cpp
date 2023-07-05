#include "runtime/NullArguments.hpp"
#include "static/string.ipp"

using elrond::runtime::NullArguments;

//
// Signed integer methods
//
elrond::int32 NullArguments::asInt(const char[]) const
{ return elrond::int32(); }

elrond::int32 NullArguments::asInt(elrond::string) const
{ return elrond::int32(); }

bool NullArguments::isInt(const char[]) const
{ return false; }

bool NullArguments::isInt(elrond::string) const
{ return false; }

//
// Unsigned integer methods
//
elrond::uInt32 NullArguments::asUInt(const char[]) const
{ return elrond::uInt32(); }

elrond::uInt32 NullArguments::asUInt(elrond::string) const
{ return elrond::uInt32(); }

bool NullArguments::isUInt(const char[]) const
{ return false; }

bool NullArguments::isUInt(elrond::string) const
{ return false; }

//
// Boolean methods
//
bool NullArguments::asBool(const char[]) const
{ return false; }

bool NullArguments::asBool(elrond::string) const
{ return false; }

bool NullArguments::isBool(const char[]) const
{ return false; }

bool NullArguments::isBool(elrond::string) const
{ return false; }

//
// Double methods
//
double NullArguments::asDouble(const char[]) const
{ return double(); }

double NullArguments::asDouble(elrond::string) const
{ return double(); }

bool NullArguments::isDouble(const char[]) const
{ return false; }

bool NullArguments::isDouble(elrond::string) const
{ return false; }

//
// String methods
//
elrond::string NullArguments::asString(const char[]) const
{ return elrond::nullstr(); }

elrond::string NullArguments::asString(elrond::string) const
{ return elrond::nullstr(); }

elrond::sizeT NullArguments::asString(
    const char[],
    char[],
    const elrond::sizeT
) const { return 0; }

elrond::sizeT NullArguments::asString(
    elrond::string,
    char[],
    const elrond::sizeT
) const { return 0; }

bool NullArguments::isString(const char[]) const
{ return false; }

bool NullArguments::isString(elrond::string) const
{ return false; }

//
// Others
//
bool NullArguments::exists(const char[]) const
{ return false; }

bool NullArguments::exists(elrond::string) const
{ return false; }
