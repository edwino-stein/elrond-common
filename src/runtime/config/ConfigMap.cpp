#include "runtime/config/ConfigMap.hpp"
#include "interfaces/ConfigMapMemoryInterface.hpp"

#if defined GENERIC_STD_PLATFORM
    #include <cstring>
    #include <cstdio>
#elif defined INO_PLATFORM
    #include <string.h>
    #include <stdio.h>
#endif

using namespace elrond::config;
using elrond::interfaces::ConfigMapMemoryInterface;

/*  ****************************************************************************
    *************** Implementation for elrond::config::ConfigMap ***************
    ****************************************************************************/

ConfigMap::ConfigMap(ConfigMapMemoryInterface &dm): dm(dm) {}

bool ConfigMap::getNext(elrond::sizeT &index) const {

    elrond::byte info = (elrond::byte) configType::N;
    this->dm.read(index, info);

    if(this->is(info, configType::N)) return false;

    elrond::sizeT size = 1 + sizeof(const char *);

    if(this->is(info, configType::INT)) size += sizeof(int);
    if(this->is(info, configType::DOUBLE)) size += sizeof(double);
    if(this->is(info, configType::STRING)) size += sizeof(const char *);

    index += size;
    return true;
}

bool ConfigMap::findKey(const char *key, elrond::sizeT &index, elrond::byte &info) const {

    index = 0;
    info = (elrond::byte) configType::N;

    for (elrond::sizeT i = 0; i < this->itens; ++i){
        const char *k = this->readString(index + 1);
        if(strcmp(k, key) == 0){
            this->dm.read(index, info);
            return true;
        }
        if(!this->getNext(index)) return false;
    }

    return false;
}

const char *ConfigMap::readString(const elrond::sizeT index) const {

    uintptr_t p = 0;
    const elrond::sizeT size = sizeof(const char *);

    for (sizeT i = 0; i < size; ++i){
        byte b = 0x0;
        if(!this->dm.read(index + i, b)) return nullptr;
        p |= ((uintptr_t) (0xFF & b) << 8 * i);
    }

    return (const char *) p;
}

int ConfigMap::readInt(const elrond::sizeT index) const {

    int v = 0;
    const elrond::sizeT size = sizeof(int);

    for (elrond::sizeT i = 0; i < size; ++i) {
        elrond::byte b = 0x0;
        this->dm.read(index + i, b);
        v |= ((int) (0xFF & b) << 8 * i);
    }

    return v;
}

double ConfigMap::readDouble(const elrond::sizeT index) const {

    doubleBytes v;
    v.value = 0;

    const elrond::sizeT size = sizeof(double);

    for (elrond::sizeT i = 0; i < size; ++i) {
        elrond::byte b = 0x0;
        this->dm.read(index + i, b);
        v.data[i] = b;
    }

    return v.value;
}

bool ConfigMap::readBool(const elrond::byte info) const {
    return (info & 0x01) == 1;
}

char ConfigMap::readChar(const elrond::byte info) const {
    return (char) (info & ~((elrond::byte) configType::CHAR));
}

int ConfigMap::asInt(const char *key) const {

    elrond::sizeT index;
    elrond::byte info;

    if(this->findKey(key, index, info)){
        if(this->is(info, configType::INT)) return this->readInt(index + 1 + sizeof(const char *));
        if(this->is(info, configType::DOUBLE)) return (int) this->readDouble(index + 1 + sizeof(const char *));
        if(this->is(info, configType::CHAR)) return (int) this->readChar(info);
        if(this->is(info, configType::BOOL)) return (int) this->readBool(info);
    }

    return 0;
}

double ConfigMap::asDouble(const char *key) const {

    elrond::sizeT index;
    elrond::byte info;

    if(this->findKey(key, index, info)){
        if(this->is(info, configType::DOUBLE)) return this->readDouble(index + 1 + sizeof(const char *));
        if(this->is(info, configType::INT)) return (double) this->readInt(index + 1 + sizeof(const char *));
        if(this->is(info, configType::CHAR)) return (double) this->readChar(info);
        if(this->is(info, configType::BOOL)) return (double) this->readBool(info);
    }

    return 0.0;
}

bool ConfigMap::asBool(const char *key) const {

    elrond::sizeT index;
    elrond::byte info;

    if(this->findKey(key, index, info)){
        if(this->is(info, configType::BOOL)) return  this->readBool(info);
        if(this->is(info, configType::CHAR)) return (bool) this->readChar(info);
        if(this->is(info, configType::INT)) return (bool) this->readInt(index + 1 + sizeof(const char *));
        if(this->is(info, configType::DOUBLE)) return (bool) this->readDouble(index + 1 + sizeof(const char *));
    }

    return false;
}

char ConfigMap::asChar(const char *key) const {

    elrond::sizeT index;
    elrond::byte info;

    if(this->findKey(key, index, info)){
        if(this->is(info, configType::CHAR)) return this->readChar(info);
        if(this->is(info, configType::INT)) return (char) this->readInt(index + 1 + sizeof(const char *));
        if(this->is(info, configType::BOOL)) return (char) this->readBool(info);
        if(this->is(info, configType::DOUBLE)) return (char) this->readDouble(index + 1 + sizeof(const char *));
    }

    return '\0';
}

const char *ConfigMap::asString(const char *key) const {

    elrond::sizeT index;
    elrond::byte info;
    if(this->findKey(key, index, info)){
        if(this->is(info, configType::STRING)) return this->readString(index + 1 + sizeof(const char *));
    }

    return "";
}

int ConfigMap::asString(const char *key, char value[]) const {

    elrond::sizeT index;
    elrond::byte info;

    if(this->findKey(key, index, info)){

        if(this->is(info, configType::STRING)) {
            return sprintf(value, "%s", this->readString(index + 1 + sizeof(const char *)));
        }

        if(this->is(info, configType::INT)) {
            return sprintf(value, "%d", this->readInt(index + 1 + sizeof(const char *)));
        }

        if(this->is(info, configType::CHAR)) {
            return sprintf(value, "%c", this->readChar(info));
        }

        if(this->is(info, configType::BOOL)) {
            return sprintf(value, "%c", this->readBool(info) ? 't' : 'f');
        }

        if(this->is(info, configType::DOUBLE)) {
            return sprintf(value, "%f", this->readDouble(index + 1 + sizeof(const char *)));
        }
    }

    return 0;
}

bool ConfigMap::is(const elrond::byte info, const enum configType type) const {

    if(type == configType::CHAR){
        return (info & (elrond::byte) configType::CHAR) == ((elrond::byte) configType::CHAR);
    }

    return (info & 0xF0) == ((elrond::byte) type);
}

bool ConfigMap::is(const char *key, const enum configType type) const {
    elrond::sizeT index;
    elrond::byte info;
    if(!this->findKey(key, index, info)) info = (elrond::byte) configType::N;
    return this->is(info, type);
}

bool ConfigMap::isInt(const char *key) const { return this->is(key, configType::INT); }
bool ConfigMap::isDouble(const char *key) const { return this->is(key, configType::DOUBLE); }
bool ConfigMap::isBool(const char *key) const { return this->is(key, configType::BOOL); }
bool ConfigMap::isChar(const char *key) const { return this->is(key, configType::CHAR); }
bool ConfigMap::isString(const char *key) const { return this->is(key, configType::STRING); }
bool ConfigMap::isNull(const char *key) const { return this->is(key, configType::N); }
