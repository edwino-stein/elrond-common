#ifndef ELROND_MOCK_ARGUMENTS_HPP
    #define ELROND_MOCK_ARGUMENTS_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class Arguments : public elrond::interface::Arguments
            {
                private:

                    template <class T> struct Value;
                    struct Null;
                    struct Int;
                    struct UInt;
                    struct Bool;
                    struct Double;
                    struct String;

                public:

                    struct ValueBase
                    {
                        using Ptr = std::shared_ptr<ValueBase>;
                        virtual ~ValueBase() = default;

                        virtual elrond::int32 asInt() const =0;
                        virtual elrond::uInt32 asUInt() const =0;
                        virtual bool asBool() const =0;
                        virtual double asDouble() const =0;
                        virtual elrond::string asString() const =0;
                    };

                protected:

                    std::map<elrond::string, ValueBase::Ptr> values;

                public:

                    //
                    // Signed integer methods
                    //
                    elrond::int32 asInt(const char key[]) const override;
                    elrond::int32 asInt(elrond::string key) const override;
                    bool isInt(const char key[]) const override;
                    bool isInt(elrond::string key) const override;

                    Arguments& set(const elrond::string& key, const elrond::int32 i);

                    //
                    // Unsigned integer methods
                    //
                    elrond::uInt32 asUInt(const char key[]) const override;
                    elrond::uInt32 asUInt(elrond::string key) const override;
                    bool isUInt(const char key[]) const override;
                    bool isUInt(elrond::string key) const override;

                    Arguments& set(const elrond::string& key, const elrond::uInt32 i);

                    //
                    // Boolean methods
                    //
                    bool asBool(const char key[]) const override;
                    bool asBool(elrond::string key) const override;
                    bool isBool(const char key[]) const override;
                    bool isBool(elrond::string key) const override;

                    Arguments& set(const elrond::string& key, const bool b);

                    //
                    // Double methods
                    //
                    double asDouble(const char key[]) const override;
                    double asDouble(elrond::string key) const override;
                    bool isDouble(const char key[]) const override;
                    bool isDouble(elrond::string key) const override;

                    Arguments& set(const elrond::string& key, const double d);

                    //
                    // String methods
                    //
                    elrond::string asString(const char key[]) const override;
                    elrond::string asString(elrond::string key) const override;

                    elrond::sizeT asString( const char key[],
                                            char value[],
                                            const elrond::sizeT len) const override;

                    elrond::sizeT asString( elrond::string key,
                                            char value[],
                                            const elrond::sizeT len) const override;

                    bool isString(const char key[]) const override;
                    bool isString(elrond::string key) const override;

                    Arguments& set(const elrond::string& key, const char* s);
                    Arguments& set(const elrond::string& key, const elrond::string& s);

                    //
                    // Others
                    //
                    bool exists(const char key[]) const override;
                    bool exists(elrond::string key) const override;

                    ValueBase::Ptr getValue(const elrond::string& key) const;
                    elrond::sizeT total() const;
                    void clear();

                    static Arguments* null();
            };
        }
    }

#endif
