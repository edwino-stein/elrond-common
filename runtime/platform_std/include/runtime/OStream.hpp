#ifndef ELROND_PLATFORM_RUNTIME_RUNTIME_O_STREAM_HPP
    #define ELROND_PLATFORM_RUNTIME_RUNTIME_O_STREAM_HPP

    #include "elrond_platform_runtime_types.hpp"

    namespace elrond
    {
        namespace runtime
        {
            class OStream : public elrond::interface::Stream
            {
                private:
                    std::ostream* os;
                    std::ostream& stream() const;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(OStream, =delete, =delete, =delete, =delete, =delete)
                    OStream(std::ostream& os);

                    // Char and strings
                    elrond::interface::Stream& operator<<(char c) override;
                    elrond::interface::Stream& operator<<(unsigned char c) override;
                    elrond::interface::Stream& operator<<(const char* c) override;
                    elrond::interface::Stream& operator<<(elrond::string str) override;

                    // Numeric
                    elrond::interface::Stream& operator<<(int i) override;
                    elrond::interface::Stream& operator<<(unsigned int i) override;
                    elrond::interface::Stream& operator<<(long l) override;
                    elrond::interface::Stream& operator<<(unsigned long l) override;
                    elrond::interface::Stream& operator<<(double d) override;
            };
        }
    }

#endif
