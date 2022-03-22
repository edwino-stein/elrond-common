#ifndef ELROND_COMMON_INTERFACE_ARGUMENTS_HPP
    #define ELROND_COMMON_INTERFACE_ARGUMENTS_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Arguments
            {
                public:

                    virtual ~Arguments() = ELROND_DEFAULT_DESTRUCTOR;

                    //
                    // Signed integer methods
                    //
                    virtual elrond::int32 asInt(const char key[]) const =0;
                    virtual elrond::int32 asInt(elrond::string key) const =0;
                    virtual bool isInt(const char key[]) const =0;
                    virtual bool isInt(elrond::string key) const =0;

                    //
                    // Unsigned integer methods
                    //
                    virtual elrond::uInt32 asUInt(const char key[]) const =0;
                    virtual elrond::uInt32 asUInt(elrond::string key) const =0;
                    virtual bool isUInt(const char key[]) const =0;
                    virtual bool isUInt(elrond::string key) const =0;

                    //
                    // Boolean methods
                    //
                    virtual bool asBool(const char key[]) const =0;
                    virtual bool asBool(elrond::string key) const =0;
                    virtual bool isBool(const char key[]) const =0;
                    virtual bool isBool(elrond::string key) const =0;

                    //
                    // Double methods
                    //
                    virtual double asDouble(const char key[]) const =0;
                    virtual double asDouble(elrond::string key) const =0;
                    virtual bool isDouble(const char key[]) const =0;
                    virtual bool isDouble(elrond::string key) const =0;

                    //
                    // String methods
                    //
                    virtual elrond::string asString(const char key[]) const =0;
                    virtual elrond::string asString(elrond::string key) const =0;

                    virtual elrond::sizeT asString( const char key[],
                                                    char value[],
                                                    const elrond::sizeT len) const =0;

                    virtual elrond::sizeT asString( elrond::string key,
                                                    char value[],
                                                    const elrond::sizeT len) const =0;

                    virtual bool isString(const char key[]) const =0;
                    virtual bool isString(elrond::string key) const =0;

                    //
                    // Others
                    //
                    virtual bool exists(const char key[]) const =0;
                    virtual bool exists(elrond::string key) const =0;
            };
        }
    }

#endif
