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
                    operator<<(char) const override;

                    const elrond::interface::Stream&
                    operator<<(unsigned char) const override;

                    const elrond::interface::Stream&
                    operator<<(const char*) const override;
    
                    const elrond::interface::Stream&
                    operator<<(elrond::string) const override;

                    // Numeric
                    const elrond::interface::Stream&
                    operator<<(int) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(unsigned int) const override;

                    const elrond::interface::Stream&
                    operator<<(long) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(unsigned long) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(double) const override;
            };
        }
    }

#endif
