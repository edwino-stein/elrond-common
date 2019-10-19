#if !defined  _ELROND_CONFIG_MAP_HPP
#define _ELROND_CONFIG_MAP_HPP

    #include "types.hpp"

    namespace elrond {
        namespace config {

            class ConfigMap {

                protected:

                    enum class configType : elrond::byte {
                        N = 0x0,
                        INT = 0x10,
                        BOOL = 0x20,
                        DOUBLE = 0x30,
                        STRING = 0x40,
                        CHAR = 0x80,
                    };

                    union doubleBytes {
                        double value;
                        elrond::byte data[sizeof(double)];
                    };

                    elrond::interfaces::ConfigMapMemoryInterface &dm;
                    elrond::sizeT itens = 0;

                    bool getNext(elrond::sizeT &index) const;
                    bool findKey(const char *key, elrond::sizeT &index, elrond::byte &info) const;

                    const char *readString(const elrond::sizeT index) const;
                    int readInt(const elrond::sizeT index) const;
                    double readDouble(const elrond::sizeT index) const;
                    bool readBool(const elrond::byte info) const;
                    char readChar(const elrond::byte info) const;

                    bool is(const elrond::byte info, const enum configType type) const;
                    bool is(const char *key, const enum configType type) const;

                    ConfigMap(elrond::interfaces::ConfigMapMemoryInterface &dm);

                public:

                    int asInt(const char *key) const;
                    bool asBool(const char *key) const;
                    char asChar(const char *key) const;
                    double asDouble(const char *key) const;
                    const char *asString(const char *key) const;
                    int asString(const char *key, char value[]) const;

                    bool isInt(const char *key) const;
                    bool isDouble(const char *key) const;
                    bool isBool(const char *key) const;
                    bool isChar(const char *key) const;
                    bool isString(const char *key) const;
                    bool isNull(const char *key) const;
            };
        }
    }

#endif
