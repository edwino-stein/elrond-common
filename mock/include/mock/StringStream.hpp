#ifndef ELROND_MOCK_STRING_STREAM_HPP
    #define ELROND_MOCK_STRING_STREAM_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class StringStream : public elrond::platform::OStream
            {
                private:
                    std::ostringstream oss;

                public:
                    StringStream();

                    virtual std::string getString() const;
                    virtual void flush();
            };
        }
    }

#endif
