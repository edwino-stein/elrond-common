#if !defined  _ELROND_TEST_CONFIG_MAP_HPP
#define _ELROND_TEST_CONFIG_MAP_HPP

    #include "elrond.hpp"
    #include <map>
    #include <memory>
    #include <string>

    namespace elrond {
        namespace test {

            class ConfigMap : public elrond::interfaces::ConfigMapInterface {

                private:

                    enum class DataType {
                        DATA_TYPE_INT,
                        DATA_TYPE_DOUBLE,
                        DATA_TYPE_BOOL,
                        DATA_TYPE_STRING
                    };

                    struct DataGenericValue {
                        const DataType type;
                        DataGenericValue(const DataType type): type(type){}
                    };

                    template<class T, DataType V>
                    struct DataValue : public DataGenericValue {
                        const T value;
                        DataValue(T value) : DataGenericValue(V), value(value){}
                    };

                    using DataValueP = std::shared_ptr<DataGenericValue>;
                    using DataValueMap = std::map<std::string, DataValueP>;

                protected:

                    DataValueMap data;
                    ConfigMap& set(std::string key, DataValueP value);

                public:

                    int asInt(const char* key) const override;
                    long asLong(const char* key) const override;
                    bool asBool(const char* key) const override;
                    char asChar(const char* key) const override;
                    double asDouble(const char* key) const override;
                    const char* asString(const char* key) const override;
                    int asString(const char* key, char value[], const elrond::sizeT len) const override;

                    bool isInt(const char* key) const override;
                    bool isLong(const char* key) const override;
                    bool isDouble(const char* key) const override;
                    bool isBool(const char* key) const override;
                    bool isChar(const char* key) const override;
                    bool isString(const char* key) const override;
                    bool isNull(const char* key) const override;

                    ConfigMap& set(std::string key, const char c[]);
                    ConfigMap& set(std::string key, std::string const& str);
                    ConfigMap& set(std::string key, char c);
                    ConfigMap& set(std::string key, int i);
                    ConfigMap& set(std::string key, double d);
                    ConfigMap& set(std::string key, bool b);
            };
        }
    }

#endif
