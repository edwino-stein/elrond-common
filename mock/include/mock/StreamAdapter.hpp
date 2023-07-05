#ifndef ELROND_MOCK_STREAM_ADAPTER_HPP
    #define ELROND_MOCK_STREAM_ADAPTER_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class StreamAdapter : public elrond::interface::StreamAdapter
            {
                public:
                    using AppendH = elrond::procedure<const elrond::interface::Stream&>;

                private:
                    elrond::interface::Stream& _stream;
                    AppendH _preAppend;
                    AppendH _postAppend;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(StreamAdapter, =delete, =default, =default, =default, =default)
                    StreamAdapter(elrond::interface::Stream& stream, AppendH preAppend, AppendH postAppend);

                    const elrond::interface::Stream& stream() const override;
                    void preAppend() const override;
                    void postAppend() const override;

                    static void eolAppend(const elrond::interface::Stream& stream);
                    static void voidAppend(const elrond::interface::Stream& stream);

                    static elrond::pointer<elrond::interface::StreamAdapter> makePretty(elrond::interface::Stream& stream, elrond::string tag);
                    static elrond::pointer<elrond::interface::StreamAdapter> makeNull(elrond::interface::Stream& stream, elrond::string tag);
            };

        }
    }

#endif
