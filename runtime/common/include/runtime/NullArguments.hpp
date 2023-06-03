#ifndef EELROND_COMMON_RUNTIME_RUNTIME_NULL_ARGUMENTS_HPP
    #define EELROND_COMMON_RUNTIME_RUNTIME_NULL_ARGUMENTS_HPP

    #include "elrond_common_runtime_types.hpp"

    namespace elrond
    {
        namespace runtime
        {
            class NullArguments : public elrond::interface::Arguments
            {
                public:
                    //
                    // Signed integer methods
                    //
                    elrond::int32 asInt(const char key[]) const override;
                    elrond::int32 asInt(elrond::string key) const override;
                    bool isInt(const char key[]) const override;
                    bool isInt(elrond::string key) const override;

                    //
                    // Unsigned integer methods
                    //
                    elrond::uInt32 asUInt(const char key[]) const override;
                    elrond::uInt32 asUInt(elrond::string key) const override;
                    bool isUInt(const char key[]) const override;
                    bool isUInt(elrond::string key) const override;

                    //
                    // Boolean methods
                    //
                    bool asBool(const char key[]) const override;
                    bool asBool(elrond::string key) const override;
                    bool isBool(const char key[]) const override;
                    bool isBool(elrond::string key) const override;

                    //
                    // Double methods
                    //
                    double asDouble(const char key[]) const override;
                    double asDouble(elrond::string key) const override;
                    bool isDouble(const char key[]) const override;
                    bool isDouble(elrond::string key) const override;

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

                    //
                    // Others
                    //
                    bool exists(const char key[]) const override;
                    bool exists(elrond::string key) const override;
            };
        }
    }

#endif
