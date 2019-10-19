#include "runtime/config/ConfigMapAllocator.hpp"
#include "interfaces/ConfigMapMemoryInterface.hpp"

using namespace elrond::config;
using elrond::interfaces::ConfigMapMemoryInterface;
using elrond::config::ConfigMap;

/*  ****************************************************************************
    ********** Implementation for elrond::config::ConfigMapAllocator **********
    ****************************************************************************/

ConfigMapAllocator::ConfigMapAllocator(ConfigMapMemoryInterface &dm): ConfigMap(dm){}

void ConfigMapAllocator::write(elrond::byte data){
    this->dm.write(data);
}

void ConfigMapAllocator::write(const char *key){

    uintptr_t pointer = (uintptr_t) key;
    const elrond::sizeT size = sizeof(const char *);

    for(elrond::sizeT i = 0; i < size; ++i)
        this->write((elrond::byte)(pointer >> 8 * i));
}

void ConfigMapAllocator::push(const char *key, int value){

    const elrond::sizeT size = sizeof(int);
    if(!this->dm.alloc(sizeof(const char *) + size + 1)) return;

    this->write((elrond::byte) configType::INT);
    this->write(key);

    for(elrond::sizeT i = 0; i < size; ++i)
        this->write((elrond::byte)(value >> 8*i));

    this->itens++;
}

void ConfigMapAllocator::push(const char *key, double value){

    const elrond::sizeT size = sizeof(double);
    if(!this->dm.alloc(sizeof(const char *) + size + 1)) return;

    this->write((elrond::byte) configType::DOUBLE);
    this->write(key);

    doubleBytes db;
    db.value = value;
    for(elrond::sizeT i = 0; i < size; ++i) this->write(db.data[i]);

    this->itens++;
}

void ConfigMapAllocator::push(const char *key, bool value){
    if(!this->dm.alloc(sizeof(const char *) + 1)) return;
    this->write(((elrond::byte) configType::BOOL) | (value ? 0x01 : 0x00));
    this->write(key);
    this->itens++;
}

void ConfigMapAllocator::push(const char *key, char value){
    if(!this->dm.alloc(sizeof(const char *) + 1)) return;
    this->write((elrond::byte) configType::CHAR | value);
    this->write(key);
    this->itens++;
}

void ConfigMapAllocator::push(const char *key, const char *value){

    const elrond::sizeT size = sizeof(const char *);
    if(!this->dm.alloc(sizeof(const char *) + size + 1)) return;

    this->write((elrond::byte) configType::STRING);
    this->write(key);
    this->write(value);

    this->itens++;
}
