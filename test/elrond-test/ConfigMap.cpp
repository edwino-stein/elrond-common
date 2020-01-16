#include "elrond-test/ConfigMap.hpp"

using elrond::test::ConfigMap;
using elrond::interfaces::ConfigMapInterface;

int ConfigMap::asInt(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_INT) return 0;
    return ((ConfigMap::DataValue<int, ConfigMap::DataType::DATA_TYPE_INT> *) it->second.get())->value;
}

long ConfigMap::asLong(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_INT) return 0;
    return ((ConfigMap::DataValue<int, ConfigMap::DataType::DATA_TYPE_INT> *) it->second.get())->value;
}

bool ConfigMap::asBool(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_BOOL) return false;
    return ((ConfigMap::DataValue<bool, ConfigMap::DataType::DATA_TYPE_BOOL> *) it->second.get())->value;
}

double ConfigMap::asDouble(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_DOUBLE) return 0;
    return ((ConfigMap::DataValue<double, ConfigMap::DataType::DATA_TYPE_DOUBLE> *) it->second.get())->value;
}

char ConfigMap::asChar(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_STRING) return 0;
    std::string s = ((ConfigMap::DataValue<std::string, ConfigMap::DataType::DATA_TYPE_STRING> *) it->second.get())->value;
    return s.size() > 0 ? s.at(0) : 0;
}

const char* ConfigMap::asString(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return "";
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_STRING) return "";
    return ((ConfigMap::DataValue<std::string, ConfigMap::DataType::DATA_TYPE_STRING> *) it->second.get())->value.c_str();
}

int ConfigMap::asString(const char* key, char value[], const elrond::sizeT len) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return 0;
    if(it->second->type != ConfigMap::DataType::DATA_TYPE_STRING) return 0;
    std::string s = ((ConfigMap::DataValue<std::string, ConfigMap::DataType::DATA_TYPE_STRING> *) it->second.get())->value;
    return s.copy(value, len, 0);
}

bool ConfigMap::isInt(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_INT;
}

bool ConfigMap::isLong(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_INT;
}

bool ConfigMap::isDouble(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_DOUBLE;
}

bool ConfigMap::isBool(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_BOOL;
}

bool ConfigMap::isChar(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_STRING;
}

bool ConfigMap::isString(const char* key) const
{
    auto it = this->data.find(key);
    if(it == this->data.end()) return false;
    return it->second->type == DataType::DATA_TYPE_STRING;
}

bool ConfigMap::isNull(const char* key) const
{
    auto it = this->data.find(key);
    return it == this->data.end();
}

ConfigMap& ConfigMap::set(std::string key, DataValueP value){
    auto it = this->data.find(key);
    if(it != this->data.end()) this->data.erase(it);
    this->data[key] = value;
    return *this;
}

ConfigMap& ConfigMap::set(std::string key, const char c[])
{
    return this->set(
        key,
        std::make_shared<ConfigMap::DataValue<std::string, ConfigMap::DataType::DATA_TYPE_STRING>>(c)
    );
}

ConfigMap& ConfigMap::set(std::string key, std::string const& str)
{
    return this->set(
        key,
        std::make_shared<ConfigMap::DataValue<std::string, ConfigMap::DataType::DATA_TYPE_STRING>>(str)
    );
}

ConfigMap& ConfigMap::set(std::string key, char c)
{
    std::string s = "";
    s += c;
    return this->set(
        key,
        std::make_shared<ConfigMap::DataValue<std::string, ConfigMap::DataType::DATA_TYPE_STRING>>(s)
    );
}

ConfigMap& ConfigMap::set(std::string key, int i)
{
    return this->set(
        key,
        std::make_shared<ConfigMap::DataValue<int, ConfigMap::DataType::DATA_TYPE_INT>>(i)
    );
}

ConfigMap& ConfigMap::set(std::string key, double d)
{
    return this->set(
        key,
        std::make_shared<ConfigMap::DataValue<double, ConfigMap::DataType::DATA_TYPE_DOUBLE>>(d)
    );
}

ConfigMap& ConfigMap::set(std::string key, bool b)
{
    return this->set(
        key,
        std::make_shared<ConfigMap::DataValue<bool, ConfigMap::DataType::DATA_TYPE_BOOL>>(b)
    );
}
