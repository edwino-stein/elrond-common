#ifndef ELROND_COMMON_RUNTIME_RUNTIME_NULL_STREAM_HPP
    #define ELROND_COMMON_RUNTIME_RUNTIME_NULL_STREAM_HPP

    #include "elrond_common_runtime_types.hpp"

    namespace elrond
    {
        namespace runtime
        {
            class NullStream : public elrond::interface::Stream
            {
                public:

                    NullStream();

                    // Char and strings
                    const elrond::interface::Stream&
                    operator<<(const char) const override;

                    const elrond::interface::Stream&
                    operator<<(const unsigned char) const override;

                    const elrond::interface::Stream&
                    operator<<(const char[]) const override;
    
                    const elrond::interface::Stream&
                    operator<<(elrond::string) const override;

                    // Numeric
                    const elrond::interface::Stream&
                    operator<<(const int) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(const unsigned int) const override;

                    const elrond::interface::Stream&
                    operator<<(const long) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(const unsigned long) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(const double) const override;
            };
        }
    }

#endif
