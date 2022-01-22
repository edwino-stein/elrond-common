#ifndef ELROND_PLATFORM_RUNTIME_STREAM_HPP
    #define ELROND_PLATFORM_RUNTIME_STREAM_HPP

    #include "elrond_platform_runtime_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            class OStream : public elrond::interface::Stream
            {
                private:
                    std::ostream* os;
                    std::ostream& stream() const;

                public:

                    OStream(std::ostream& os);
                    virtual ~OStream() = default;

                    // Char and strings
                    const elrond::interface::Stream&
                    operator<<(const char c) const override;

                    const elrond::interface::Stream&
                    operator<<(const unsigned char c) const override;

                    const elrond::interface::Stream&
                    operator<<(const char c[]) const override;
    
                    const elrond::interface::Stream&
                    operator<<(elrond::string str) const override;

                    // Numeric
                    const elrond::interface::Stream&
                    operator<<(const int i) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(const unsigned int i) const override;

                    const elrond::interface::Stream&
                    operator<<(const long l) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(const unsigned long l) const override;
                    
                    const elrond::interface::Stream&
                    operator<<(const double d) const override;
            };
        }
    }

#endif
