#ifndef ELROND_COMMON_INTERFACE_CONTEXT_HPP
    #define ELROND_COMMON_INTERFACE_CONTEXT_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Context
            {
                public:

                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(Context)

                    virtual elrond::pointer<elrond::interface::Console> console() const =0;
                    virtual elrond::pointer<elrond::interface::Arguments> arguments() const =0;
                    virtual elrond::string name() const =0;

                    virtual void setLoopEvery(const elrond::TimeSpan& ts) =0;
                    virtual void unsetLoop() =0;
            };
        }
    }

#endif
