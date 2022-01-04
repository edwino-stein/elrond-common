#ifndef ELROND_COMMON_INTERFACE_PARAMETERS_HPP
    #define ELROND_COMMON_INTERFACE_PARAMETERS_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Parameters
            {
                public:
                    virtual ~Parameters() = ELROND_DEFAULT_DESTRUCTOR;

                    //
                    // C string key based
                    //
                    virtual int asInt(const char key[]) const =0;
                    virtual long asLong(const char key[]) const =0;
                    virtual bool asBool(const char key[]) const =0;
                    virtual char asChar(const char key[]) const =0;
                    virtual double asDouble(const char key[]) const =0;
                    virtual elrond::string asString(const char key[]) const =0;
                    virtual elrond::sizeT asString( const char key[],
                                                    char value[],
                                                    const elrond::sizeT len) const =0;

                    virtual bool isInt(const char key[]) const =0;
                    virtual bool isLong(const char key[]) const =0;
                    virtual bool isDouble(const char key[]) const =0;
                    virtual bool isBool(const char key[]) const =0;
                    virtual bool isChar(const char key[]) const =0;
                    virtual bool isString(const char key[]) const =0;
                    virtual bool exists(const char key[]) const =0;

                    //
                    // Elrond string key based
                    //
                    virtual int asInt(elrond::string key) const =0;
                    virtual long asLong(elrond::string key) const =0;
                    virtual bool asBool(elrond::string key) const =0;
                    virtual char asChar(elrond::string key) const =0;
                    virtual double asDouble(elrond::string key) const =0;
                    virtual elrond::string asString(elrond::string key) const =0;
                    virtual elrond::sizeT asString( elrond::string key,
                                                    char value[],
                                                    const elrond::sizeT len) const =0;

                    virtual bool isInt(elrond::string key) const =0;
                    virtual bool isLong(elrond::string key) const =0;
                    virtual bool isDouble(elrond::string key) const =0;
                    virtual bool isBool(elrond::string key) const =0;
                    virtual bool isChar(elrond::string key) const =0;
                    virtual bool isString(elrond::string key) const =0;
                    virtual bool exists(elrond::string key) const =0;
            };
        }
    }

#endif
