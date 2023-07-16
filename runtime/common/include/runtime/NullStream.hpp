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

                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(NullStream)

                    // Char and strings
                    elrond::interface::Stream& operator<<(char) override;
                    elrond::interface::Stream& operator<<(unsigned char) override;
                    elrond::interface::Stream& operator<<(const char*) override;
                    elrond::interface::Stream& operator<<(elrond::string) override;

                    // Numeric
                    elrond::interface::Stream& operator<<(int) override;
                    elrond::interface::Stream& operator<<(unsigned int) override;
                    elrond::interface::Stream& operator<<(long) override;
                    elrond::interface::Stream& operator<<(unsigned long) override;
                    elrond::interface::Stream& operator<<(double) override;
            };
        }
    }

#endif
