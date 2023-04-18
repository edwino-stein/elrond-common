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

                    ELROND_OPT_DFLT_VDESTRUCTOR(Context);

                    virtual elrond::pointer<elrond::interface::Console> console() const =0;
                    virtual elrond::pointer<elrond::interface::Arguments> arguments() const =0;
                    virtual elrond::string name() const =0;

                    virtual void loopEnable(bool enable) =0;
                    virtual void loopInterval(elrond::timeT interval) =0;
                    virtual void loopAsync(bool enable) =0;
            };
        }
    }

#endif
