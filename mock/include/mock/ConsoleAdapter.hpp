#ifndef ELROND_MOCK_CONSOLE_ADAPTER_HPP
    #define ELROND_MOCK_CONSOLE_ADAPTER_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class ConsoleAdapter : public elrond::interface::ConsoleAdapter
            {
                public:
                    using MakeStreamH = elrond::function<elrond::pointer<elrond::interface::Stream>>;
                    using AppendH = elrond::procedure<elrond::interface::Stream&, const elrond::string&, elrond::interface::ConsoleAdapter::SEVERITY>;

                protected:
                    MakeStreamH _makeStream;
                    AppendH _preAppend;
                    AppendH _postAppend;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(ConsoleAdapter, =delete, =delete, =delete, =delete, =delete)
                    ConsoleAdapter(MakeStreamH makeStream);
                    ConsoleAdapter(MakeStreamH makeStream, AppendH preAppend);
                    ConsoleAdapter(MakeStreamH makeStream, AppendH preAppend, AppendH postAppend);

                    void preAppend( elrond::interface::Stream& stream,
                                    const elrond::string& tag,
                                    elrond::interface::ConsoleAdapter::SEVERITY severity) const override;

                    void postAppend(elrond::interface::Stream& stream,
                                    const elrond::string& tag,
                                    elrond::interface::ConsoleAdapter::SEVERITY severity) const override;

                    elrond::pointer<elrond::interface::Stream> makeStream() const override;

                    static ConsoleAdapter& null();
                    static void nullAppend(elrond::interface::Stream&, const elrond::string&, ConsoleAdapter::SEVERITY);
                    static elrond::pointer<elrond::interface::Stream> makeNullStream();
            };
        }
    }

#endif
