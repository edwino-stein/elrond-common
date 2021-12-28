#ifndef ELROND_MOCK_PARAMETERS_HPP
    #define ELROND_MOCK_PARAMETERS_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class Parameters : public elrond::interface::Parameters
            {
                private:

                    template <class T> struct ValueType;
                    struct Null;
                    struct Int;
                    struct Long;
                    struct Bool;
                    struct Char;
                    struct Double;
                    struct String;

                public:

                    struct ValueBase
                    {
                        using Ptr = std::shared_ptr<ValueBase>;
                        virtual int asInt() const =0;
                        virtual long asLong() const =0;
                        virtual bool asBool() const =0;
                        virtual char asChar() const =0;
                        virtual double asDouble() const =0;
                        virtual elrond::string asString() const =0;
                    };

                protected:
                    std::map<const elrond::string, ValueBase::Ptr> values;

                public:

                    ValueBase::Ptr getValue(const elrond::string& key) const;
                    elrond::sizeT total() const;

                    //
                    // C string key based
                    //
                    int asInt(const char key[]) const override;
                    long asLong(const char key[]) const override;
                    bool asBool(const char key[]) const override;
                    char asChar(const char key[]) const override;
                    double asDouble(const char key[]) const override;
                    elrond::string asString(const char key[]) const override;
                    elrond::sizeT asString( const char key[],
                                            char value[],
                                            const elrond::sizeT len) const override;

                    bool isInt(const char key[]) const override;
                    bool isLong(const char key[]) const override;
                    bool isDouble(const char key[]) const override;
                    bool isBool(const char key[]) const override;
                    bool isChar(const char key[]) const override;
                    bool isString(const char key[]) const override;
                    bool exists(const char key[]) const override;

                    //
                    // Elrond string key based
                    //
                    int asInt(elrond::string key) const override;
                    long asLong(elrond::string key) const override;
                    bool asBool(elrond::string key) const override;
                    char asChar(elrond::string key) const override;
                    double asDouble(elrond::string key) const override;
                    elrond::string asString(elrond::string key) const override;
                    elrond::sizeT asString( elrond::string key,
                                            char value[],
                                            const elrond::sizeT len) const override;

                    bool isInt(elrond::string key) const override;
                    bool isLong(elrond::string key) const override;
                    bool isDouble(elrond::string key) const override;
                    bool isBool(elrond::string key) const override;
                    bool isChar(elrond::string key) const override;
                    bool isString(elrond::string key) const override;
                    bool exists(elrond::string key) const override;

                    //
                    // Setters
                    //
                    Parameters& set(const elrond::string& key, const int i);
                    Parameters& set(const elrond::string& key, const long l);
                    Parameters& set(const elrond::string& key, const bool b);
                    Parameters& set(const elrond::string& key, const char c);
                    Parameters& set(const elrond::string& key, const double d);
                    Parameters& set(const elrond::string& key, const char* s);
                    Parameters& set(const elrond::string& key, const elrond::string& s);
            };
        }
    }

#endif
