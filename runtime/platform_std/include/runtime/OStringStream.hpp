#ifndef ELROND_PLATFORM_RUNTIME_RUNTIME_O_STRING_STREAM_HPP
    #define ELROND_PLATFORM_RUNTIME_RUNTIME_O_STRING_STREAM_HPP

    #include "runtime/OStream.hpp"

    namespace elrond
    {
        namespace runtime
        {
            class OStringStream : public elrond::runtime::OStream
            {
                private:
                    std::ostringstream _oss;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(OStringStream,, =delete, =delete, =delete, =delete)
                    std::ostringstream& oss();
            };
        }
    }

#endif
