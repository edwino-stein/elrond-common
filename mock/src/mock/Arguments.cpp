#include "mock/Arguments.hpp"

using elrond::mock::Arguments;
using ValueBase = elrond::mock::Arguments::ValueBase;

/*  ****************************************************************************
    ************** elrond::mock::Arguments Types Implementation ****************
    ****************************************************************************/

/* ******************************* Base typed *************************s******* */

template <class T>
struct Arguments::Value : public ValueBase
{
    const T value;

    Value(const T value) : value(value) {}
    virtual ~Value() = default;

    static bool isTypeOf(ValueBase::Ptr obj)
    {
        return dynamic_cast<Value<T>*>(obj.get()) != nullptr;
    }
};

/* ******************************** Null type ********************************* */

struct Arguments::Null : public Arguments::ValueBase
{
    virtual ~Null() = default;

    elrond::int32 asInt() const override { return elrond::int32(); };
    elrond::uInt32 asUInt() const override { return elrond::uInt32(); };
    bool asBool() const override { return false; };
    double asDouble() const override { return double(); };
    elrond::string asString() const override { return std::string(); };
};

/* **************************** Signed integer type *************************** */

struct Arguments::Int : public Arguments::Value<elrond::int32>
{
    Int(const elrond::int32 i) : Value(i) {}
    virtual ~Int() = default;

    elrond::int32 asInt() const override
    {
        return this->value;
    }

    elrond::uInt32 asUInt() const override 
    {
        return static_cast<elrond::uInt32>(this->value);
    }

    bool asBool() const override
    {
        return this->value != 0;
    }

    double asDouble() const override
    {
        return static_cast<double>(this->value);
    }
    
    elrond::string asString() const override
    {
        return std::to_string(this->value);
    }
};

/* *************************** Unsigned integer type ************************** */

struct Arguments::UInt : public Arguments::Value<elrond::uInt32>
{
    UInt(const elrond::uInt32 i) : Value(i) {}
    virtual ~UInt() = default;

    elrond::int32 asInt() const override
    {
        return static_cast<elrond::int32>(this->value);
    }

    elrond::uInt32 asUInt() const override 
    {
        return this->value;
    }

    bool asBool() const override
    {
        return this->value != 0;
    }

    double asDouble() const override
    {
        return static_cast<double>(this->value);
    }
    
    elrond::string asString() const override
    {
        return std::to_string(this->value);
    }
};

/* ******************************** Bool type ********************************* */

struct Arguments::Bool : public Arguments::Value<bool>
{
    Bool(const bool b) : Value(b) {}
    virtual ~Bool() = default;

    elrond::int32 asInt() const override
    {
        return this->value ? 1 : 0;
    }

    elrond::uInt32 asUInt() const override 
    {
        return this->value ? 1 : 0;
    }

    bool asBool() const override
    {
        return this->value;
    }

    double asDouble() const override
    {
        return this->value ? 1.0 : 0.0;
    }
    
    elrond::string asString() const override
    {
        return this->value ? "true" : "false";
    }
};

/* ******************************* Double type ******************************** */

struct Arguments::Double : public Arguments::Value<double>
{
    Double(const double d) : Value(d) {}
    virtual ~Double() = default;

    elrond::int32 asInt() const override
    {
        return static_cast<elrond::int32>(this->value);
    }

    elrond::uInt32 asUInt() const override 
    {
        return static_cast<elrond::uInt32>(this->value);
    }

    bool asBool() const override
    {
        return this->value != 0;
    }

    double asDouble() const override
    {
        return this->value;
    }
    
    elrond::string asString() const override
    {
        return std::to_string(this->value);
    }
};

/* ******************************* String type ******************************** */

struct Arguments::String : public Arguments::Value<elrond::string>
{
    String(const elrond::string s) : Value(s) {}
    virtual ~String() = default;

    elrond::int32 asInt() const override
    {
        try { return std::stoi(this->value); }
        catch (const std::exception&) { return 0; }
    }

    elrond::uInt32 asUInt() const override 
    {
        try { return std::stoul(this->value); }
        catch (const std::exception&) { return 0; }
    }

    bool asBool() const override
    {
        return this->asInt() != 0;
    }

    double asDouble() const override
    {
        try { return std::stod(this->value); }
        catch (const std::exception&) { return 0; }
    }
    
    elrond::string asString() const override
    {
        return this->value;
    }
};

/*  ****************************************************************************
    ***************** elrond::mock::Arguments Implementation *******************
    ****************************************************************************/

/* ***************************** Others methods ****************************** */

bool Arguments::exists(const char key[]) const
{
    return this->exists(std::string(key));
}

bool Arguments::exists(elrond::string key) const
{
    return this->values.find(key) != this->values.cend();
}

elrond::sizeT Arguments::total() const
{
    return this->values.size();
}

ValueBase::Ptr Arguments::getValue(const elrond::string& key) const
{
    auto it = this->values.find(key);
    return it != this->values.cend() ? it->second : std::make_shared<Null>();
}

void Arguments::clear()
{
    this->values.clear();
}

/* ************************* Signed integer methods ************************** */

elrond::int32 Arguments::asInt(const char key[]) const
{
    return this->asInt(std::string(key));
}

elrond::int32 Arguments::asInt(elrond::string key) const
{
    return this->getValue(key)->asInt();
}

bool Arguments::isInt(const char key[]) const
{
    return this->isInt(std::string(key));
}

bool Arguments::isInt(elrond::string key) const
{
    return Int::isTypeOf(this->getValue(key));
}

Arguments& Arguments::set(const elrond::string& key, const elrond::int32 i)
{
    this->values[key] = std::make_shared<Int>(i);
    return *this;
}

/* ************************ Unsigned integer methods ************************* */

elrond::uInt32 Arguments::asUInt(const char key[]) const
{
    return this->asUInt(std::string(key));
}

elrond::uInt32 Arguments::asUInt(elrond::string key) const
{
    return this->getValue(key)->asUInt();
}

bool Arguments::isUInt(const char key[]) const
{
    return this->isUInt(std::string(key));
}

bool Arguments::isUInt(elrond::string key) const
{
    return UInt::isTypeOf(this->getValue(key));
}

Arguments& Arguments::set(const elrond::string& key, const elrond::uInt32 i)
{
    this->values[key] = std::make_shared<UInt>(i);
    return *this;
}

/* **************************** Boolean methods ****************************** */

bool Arguments::asBool(const char key[]) const
{
    return this->asBool(std::string(key));
}

bool Arguments::asBool(elrond::string key) const
{
    return this->getValue(key)->asBool();
}

bool Arguments::isBool(const char key[]) const
{
    return this->isBool(std::string(key));
}

bool Arguments::isBool(elrond::string key) const
{
    return Bool::isTypeOf(this->getValue(key));
}

Arguments& Arguments::set(const elrond::string& key, const bool b)
{
    this->values[key] = std::make_shared<Bool>(b);
    return *this;
}

/* ***************************** Double methods ****************************** */


double Arguments::asDouble(const char key[]) const
{
    return this->asDouble(std::string(key));
}

double Arguments::asDouble(elrond::string key) const
{
    return this->getValue(key)->asDouble();
}

bool Arguments::isDouble(const char key[]) const
{
    return this->isDouble(std::string(key));
}

bool Arguments::isDouble(elrond::string key) const
{
    return Double::isTypeOf(this->getValue(key));
}

Arguments& Arguments::set(const elrond::string& key, const double d)
{
    this->values[key] = std::make_shared<Double>(d);
    return *this;
}

/* ***************************** String methods ****************************** */

elrond::string Arguments::asString(const char key[]) const
{
    return this->asString(std::string(key));
}

elrond::string Arguments::asString(elrond::string key) const
{
    return this->getValue(key)->asString();
}

elrond::sizeT Arguments::asString(
    const char key[],
    char value[],
    const elrond::sizeT len) const
{
    return this->asString(std::string(key), value, len);
}

elrond::sizeT Arguments::asString(
    elrond::string key,
    char value[],
    const elrond::sizeT len) const
{
    return elrond::strCpy(this->asString(key), value, len);
}

bool Arguments::isString(const char key[]) const
{
    return this->isString(std::string(key));
}

bool Arguments::isString(elrond::string key) const
{
    return String::isTypeOf(this->getValue(key));
}

Arguments& Arguments::set(const elrond::string& key, const char* s)
{
    return this->set(key, std::string(s));
}

Arguments& Arguments::set(const elrond::string& key, const elrond::string& s)
{
    this->values[key] = std::make_shared<String>(s);
    return *this;
}
