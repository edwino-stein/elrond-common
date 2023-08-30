#ifndef ELROND_MOCK_CONSOLE_ADAPTER_HPP
    #define ELROND_MOCK_CONSOLE_ADAPTER_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class ConsoleAdapter
            {
                public:
                    using MakeStreamH = elrond::function<elrond::pointer<elrond::interface::Stream>>;
                    using AppendH = elrond::procedure<elrond::interface::ConsoleStreamAdapter&, elrond::SEVERITY>;

                    MakeStreamH _makeStream;
                    AppendH _preAppend;
                    AppendH _postAppend;

                    ELROND_CLASS_SPECIAL_MEMBERS(ConsoleAdapter, =delete, =delete, =delete, =delete, =delete)
                    ConsoleAdapter(MakeStreamH makeStream);
                    ConsoleAdapter(MakeStreamH makeStream, AppendH preAppend);
                    ConsoleAdapter(MakeStreamH makeStream, AppendH preAppend, AppendH postAppend);

                    elrond::pointer<ConsoleStreamAdapter> makeConsoleStreamAdapter();

                    static ConsoleAdapter& null();
                    static void nullAppend(elrond::interface::ConsoleStreamAdapter&, elrond::SEVERITY);
                    static elrond::pointer<elrond::interface::Stream> makeNullStream();
            };

            class ConsoleStreamAdapter : public elrond::interface::ConsoleStreamAdapter
            {
                protected:
                    ConsoleAdapter* _adapter;
                    elrond::pointer<elrond::interface::Stream> _stream;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(ConsoleStreamAdapter, =delete, =delete, =delete, =delete, =delete)
                    ConsoleStreamAdapter(ConsoleAdapter& adapter);

                    void preAppend(elrond::SEVERITY severity) override;
                    void postAppend(elrond::SEVERITY severity) override;
                    elrond::interface::Stream& stream() const override;
            };
        }
    }

#endif
