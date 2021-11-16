#ifndef ELROND_MOCK_STRING_STREAM_HPP
    #define ELROND_MOCK_STRING_STREAM_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class StringStream : public elrond::interface::Stream
            {
                private:
                    std::unique_ptr<std::ostringstream> oss;
                    std::ostringstream& stream() const;

                public:
                    StringStream();

                    // Char and strings
                    virtual const elrond::interface::Stream&
                    operator<<(const char c) const override;

                    virtual const elrond::interface::Stream&
                    operator<<(const unsigned char c) const override;

                    virtual const elrond::interface::Stream&
                    operator<<(const char c[]) const override;
    
                    virtual const elrond::interface::Stream&
                    operator<<(elrond::string str) const override;

                    // Numeric
                    virtual const elrond::interface::Stream&
                    operator<<(const int i) const override;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const unsigned int i) const override;

                    virtual const elrond::interface::Stream&
                    operator<<(const long l) const override;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const unsigned long l) const override;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const double d) const override;

                    virtual std::string getString() const;
                    virtual void flush();
            };
        }
    }

#endif