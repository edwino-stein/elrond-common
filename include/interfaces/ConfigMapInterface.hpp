#if !defined  _ELROND_CONFIG_MAP_INTERFACE_HPP
#define _ELROND_CONFIG_MAP_INTERFACE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interfaces {

            class ConfigMapInterface {

                public:

                    virtual int asInt(const char* key) const =0;
                    virtual long asLong(const char* key) const =0;
                    virtual bool asBool(const char* key) const =0;
                    virtual char asChar(const char* key) const =0;
                    virtual double asDouble(const char* key) const =0;
                    virtual const char* asString(const char* key) const =0;
                    virtual int asString(const char* key, char value[], const elrond::sizeT len) const =0;

                    virtual bool isInt(const char* key) const =0;
                    virtual bool isLong(const char* key) const =0;
                    virtual bool isDouble(const char* key) const =0;
                    virtual bool isBool(const char* key) const =0;
                    virtual bool isChar(const char* key) const =0;
                    virtual bool isString(const char* key) const =0;
                    virtual bool isNull(const char* key) const =0;

            };
        }
    }

#endif
