#include "test/ConfigMapTest.hpp"

using elrond::test::ConfigMapTest;
using elrond::interface::ConfigMap;

int ConfigMapTest::asInt(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_INT) return 0;
    return ((ConfigMapTest::DataValue<int, ConfigMapTest::DataType::DATA_TYPE_INT> *) it->second.get())->value;
}

long ConfigMapTest::asLong(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_INT) return 0;
    return ((ConfigMapTest::DataValue<int, ConfigMapTest::DataType::DATA_TYPE_INT> *) it->second.get())->value;
}

bool ConfigMapTest::asBool(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_BOOL) return false;
    return ((ConfigMapTest::DataValue<bool, ConfigMapTest::DataType::DATA_TYPE_BOOL> *) it->second.get())->value;
}

double ConfigMapTest::asDouble(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_DOUBLE) return 0;
    return ((ConfigMapTest::DataValue<double, ConfigMapTest::DataType::DATA_TYPE_DOUBLE> *) it->second.get())->value;
}

char ConfigMapTest::asChar(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_STRING) return 0;
    std::string s = ((ConfigMapTest::DataValue<std::string, ConfigMapTest::DataType::DATA_TYPE_STRING> *) it->second.get())->value;
    return s.size() > 0 ? s.at(0) : 0;
}

const char* ConfigMapTest::asString(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return "";
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_STRING) return "";
    return ((ConfigMapTest::DataValue<std::string, ConfigMapTest::DataType::DATA_TYPE_STRING> *) it->second.get())->value.c_str();
}

int ConfigMapTest::asString(const char* key, char value[], const elrond::sizeT len) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMapTest::DataType::DATA_TYPE_STRING) return 0;
    std::string s = ((ConfigMapTest::DataValue<std::string, ConfigMapTest::DataType::DATA_TYPE_STRING> *) it->second.get())->value;
    return s.copy(value, len, 0);
}

bool ConfigMapTest::isInt(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_INT;
}

bool ConfigMapTest::isLong(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_INT;
}

bool ConfigMapTest::isDouble(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_DOUBLE;
}

bool ConfigMapTest::isBool(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_BOOL;
}

bool ConfigMapTest::isChar(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_STRING;
}

bool ConfigMapTest::isString(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_STRING;
}

bool ConfigMapTest::isNull(const char* key) const
{
    auto it = this->data.find(key);
    return it == this->data.end();
}

ConfigMapTest& ConfigMapTest::set(std::string key, DataValueP value){
    auto it = this->data.find(key);
    if(it != this->data.end()) this->data.erase(it);
    this->data[key] = value;
    return *this;
}

ConfigMapTest& ConfigMapTest::set(std::string key, const char c[])
{
    return this->set(
        key,
        std::make_shared<ConfigMapTest::DataValue<std::string, ConfigMapTest::DataType::DATA_TYPE_STRING>>(c)
    );
}

ConfigMapTest& ConfigMapTest::set(std::string key, std::string const& str)
{
    return this->set(
        key,
        std::make_shared<ConfigMapTest::DataValue<std::string, ConfigMapTest::DataType::DATA_TYPE_STRING>>(str)
    );
}

ConfigMapTest& ConfigMapTest::set(std::string key, char c)
{
    std::string s = "";
    s += c;
    return this->set(
        key,
        std::make_shared<ConfigMapTest::DataValue<std::string, ConfigMapTest::DataType::DATA_TYPE_STRING>>(s)
    );
}

ConfigMapTest& ConfigMapTest::set(std::string key, int i)
{
    return this->set(
        key,
        std::make_shared<ConfigMapTest::DataValue<int, ConfigMapTest::DataType::DATA_TYPE_INT>>(i)
    );
}

ConfigMapTest& ConfigMapTest::set(std::string key, double d)
{
    return this->set(
        key,
        std::make_shared<ConfigMapTest::DataValue<double, ConfigMapTest::DataType::DATA_TYPE_DOUBLE>>(d)
    );
}

ConfigMapTest& ConfigMapTest::set(std::string key, bool b)
{
    return this->set(
        key,
        std::make_shared<ConfigMapTest::DataValue<bool, ConfigMapTest::DataType::DATA_TYPE_BOOL>>(b)
    );
}
