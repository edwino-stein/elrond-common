#include "mock/Parameters.hpp"

using elrond::mock::Parameters;
using ValueBase = elrond::mock::Parameters::ValueBase;

/*  ****************************************************************************
    ************** elrond::mock::Parameters Types Implementation ***************
    ****************************************************************************/

/* ******************************* Base typed *************************s******* */

template <class T>
struct Parameters::ValueType : public ValueBase
{
    const T value;
    ValueType(const T value) : value(value) {}

    virtual ~ValueType() = default;

    static bool isTypeOf(ValueBase::Ptr obj)
    {
        auto p = dynamic_cast<ValueType<T>*>(obj.get());
        return p != nullptr;
    }
};

/* ******************************** Null type ********************************* */

struct Parameters::Null : public Parameters::ValueBase
{
    virtual ~Null() = default;
    int asInt() const override { return 0; }
    long asLong() const override { return 0; }
    bool asBool() const override { return false; }
    char asChar() const override { return '\0'; }
    double asDouble() const override { return 0.0; }
    elrond::string asString() const override { return ""; }
};

/* ******************************* Integer type ******************************* */

struct Parameters::Int : public Parameters::ValueType<int>
{
    Int(const int i) : ValueType(i) {}
    virtual ~Int() = default;
    int asInt() const override { return this->value; }
    long asLong() const override { return static_cast<long>(this->value); }
    bool asBool() const override { return this->value != 0; }
    char asChar() const override { return static_cast<char>(this->value); }
    
    double asDouble() const override
    {
        return static_cast<double>(this->value);
    }
    
    elrond::string asString() const override
    {
        return std::to_string(this->value);
    }
};

/* ******************************** Long type ********************************* */

struct Parameters::Long : public Parameters::ValueType<long>
{
    Long(const long l) : ValueType(l) {}
    virtual ~Long() = default;
    int asInt() const override { return static_cast<long>(this->value); }
    long asLong() const override { return this->value; }
    bool asBool() const override { return this->value != 0; }

    char asChar() const override
    {
        return static_cast<char>(this->value);
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

struct Parameters::Bool : public Parameters::ValueType<bool>
{
    Bool(const bool b) : ValueType(b) {}
    virtual ~Bool() = default;
    int asInt() const override { return this->value ? 1 : 0; }
    long asLong() const override { return this->value ? 1 : 0; }
    bool asBool() const override { return this->value; }
    char asChar() const override { return this->value ? 't' : 'f'; }
    double asDouble() const override { return this->value ? 1.0 : 0.0; }

    elrond::string asString() const override
    {
        return this->value ? "true" : "false";
    }
};

/* ******************************** Char type ********************************* */

struct Parameters::Char : public Parameters::ValueType<char>
{
    Char(const char c) : ValueType(c) {}
    virtual ~Char() = default;
    int asInt() const override { return static_cast<int>(this->value); }
    long asLong() const override { return static_cast<long>(this->value); }
    
    bool asBool() const override
    {
        return !(this->value == '\0' || this->value == 'f' || this->value == 'F');
    }
    
    char asChar() const override { return this->value; }

    double asDouble() const override
    {
        return static_cast<double>(this->asInt());
    }
    
    elrond::string asString() const override
    {
        return std::string("") + this->value;
    }
};

/* ******************************* Double type ******************************** */

struct Parameters::Double : public Parameters::ValueType<double>
{
    Double(const double d) : ValueType(d) {}
    virtual ~Double() = default;
    int asInt() const override { return static_cast<int>(this->value); }
    long asLong() const override { return static_cast<long>(this->value); }
    bool asBool() const override { return this->value != 0; }
    char asChar() const override { return static_cast<char>(this->asInt()); }
    double asDouble() const override { return this->value; }

    elrond::string asString() const override
    {
        return std::to_string(this->value);
    }
};

/* ******************************* String type ******************************** */

struct Parameters::String : public Parameters::ValueType<elrond::string>
{
    String(const elrond::string s) : ValueType(s) {}
    virtual ~String() = default;
    int asInt() const override
    {
        try { return std::stoi(this->value); }
        catch (const std::exception&) { return 0; }
    }

    long asLong() const override
    {
        try { return std::stol(this->value); }
        catch (const std::exception&) { return 0; }
    }

    double asDouble() const override
    {
        try { return std::stod(this->value); }
        catch (const std::exception&) { return 0; }
    }

    bool asBool() const override { return this->value != ""; }
    char asChar() const override { return this->value[0]; }
    elrond::string asString() const override { return this->value; }
};

/*  ****************************************************************************
    ***************** elrond::mock::Parameters Implementation ******************
    ****************************************************************************/

/* ********************************* Getters ********************************* */

elrond::sizeT Parameters::total() const
{
    return this->values.size();
}

ValueBase::Ptr Parameters::getValue(const elrond::string& key) const
{
    auto it = this->values.find(key);
    return it != this->values.cend() ? it->second : std::make_shared<Null>();
}

//
// C string key based
//
int Parameters::asInt(const char key[]) const
{
    return this->asInt(std::string(key));
}

long Parameters::asLong(const char key[]) const
{
    return this->asLong(std::string(key));
}

bool Parameters::asBool(const char key[]) const
{
    return this->asBool(std::string(key));
}

char Parameters::asChar(const char key[]) const
{
    return this->asChar(std::string(key));
}

double Parameters::asDouble(const char key[]) const
{
    return this->asDouble(std::string(key));
}

elrond::string Parameters::asString(const char key[]) const
{
    return this->asString(std::string(key));
}

elrond::sizeT Parameters::asString(
    const char key[],
    char value[],
    const elrond::sizeT len) const
{
    return this->asString(std::string(key), value, len);
}

//
// Elrond string key based
//

int Parameters::asInt(elrond::string key) const
{
    return this->getValue(key)->asInt();
}

long Parameters::asLong(elrond::string key) const
{
    return this->getValue(key)->asLong();
}

bool Parameters::asBool(elrond::string key) const
{
    return this->getValue(key)->asBool();
}

char Parameters::asChar(elrond::string key) const
{
    return this->getValue(key)->asChar();
}

double Parameters::asDouble(elrond::string key) const
{
    return this->getValue(key)->asDouble();
}

elrond::string Parameters::asString(elrond::string key) const
{
    return this->getValue(key)->asString();
}

elrond::sizeT Parameters::asString(
    elrond::string key,
    char value[],
    const elrond::sizeT len) const
{
    return this->getValue(key)->asString().copy(value, len);
}

/* ******************************** Checkers ********************************* */

//
// C string key based
//

bool Parameters::isInt(const char key[]) const
{
    return this->isInt(std::string(key));
}

bool Parameters::isLong(const char key[]) const
{
    return this->isLong(std::string(key));
}

bool Parameters::isDouble(const char key[]) const
{
    return this->isDouble(std::string(key));
}

bool Parameters::isBool(const char key[]) const
{
    return this->isBool(std::string(key));
}

bool Parameters::isChar(const char key[]) const
{
    return this->isChar(std::string(key));
}

bool Parameters::isString(const char key[]) const
{
    return this->isString(std::string(key));
}

bool Parameters::exists(const char key[]) const
{
    return this->exists(std::string(key));
}

//
// Elrond string key based
//

bool Parameters::isInt(elrond::string key) const
{
    return ValueType<int>::isTypeOf(this->getValue(key));
}

bool Parameters::isLong(elrond::string key) const
{
    return ValueType<long>::isTypeOf(this->getValue(key));
}

bool Parameters::isDouble(elrond::string key) const
{
    return ValueType<double>::isTypeOf(this->getValue(key));
}

bool Parameters::isBool(elrond::string key) const
{
    return ValueType<bool>::isTypeOf(this->getValue(key));
}

bool Parameters::isChar(elrond::string key) const
{
    return ValueType<char>::isTypeOf(this->getValue(key));
}

bool Parameters::isString(elrond::string key) const
{
    return ValueType<elrond::string>::isTypeOf(this->getValue(key));
}

bool Parameters::exists(elrond::string key) const
{
    return this->values.find(key) != this->values.cend();
}

/* ********************************* Setters ********************************* */

Parameters& Parameters::set(const elrond::string& key, const int i)
{
    this->values[key] = std::make_shared<Int>(i);
    return *this;
}

Parameters& Parameters::set(const elrond::string& key, const long l)
{
    this->values[key] = std::make_shared<Long>(l);
    return *this;
}

Parameters& Parameters::set(const elrond::string& key, const bool b)
{
    this->values[key] = std::make_shared<Bool>(b);
    return *this;
}

Parameters& Parameters::set(const elrond::string& key, const char c)
{
    this->values[key] = std::make_shared<Char>(c);
    return *this;
}

Parameters& Parameters::set(const elrond::string& key, const double d)
{
    this->values[key] = std::make_shared<Double>(d);
    return *this;
}

Parameters& Parameters::set(const elrond::string& key, const char* s)
{
    this->values[key] = std::make_shared<String>(s);
    return *this;
}

Parameters& Parameters::set(const elrond::string& key, const elrond::string& s)
{
    this->values[key] = std::make_shared<String>(s);
    return *this;
}
