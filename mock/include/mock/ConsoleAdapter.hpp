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
                    using FlushH = elrond::procedure<elrond::interface::Stream&, elrond::SEVERITY>;

                    MakeStreamH _makeStream;
                    FlushH _flush;

                    ELROND_CLASS_SPECIAL_MEMBERS(ConsoleAdapter, =delete, =delete, =delete, =delete, =delete)
                    ConsoleAdapter(MakeStreamH makeStream);
                    ConsoleAdapter(MakeStreamH makeStream, FlushH flush);

                    elrond::pointer<ConsoleStreamAdapter> makeConsoleStreamAdapter();

                    static ConsoleAdapter& null();
                    static void nullFlush(elrond::interface::Stream&, elrond::SEVERITY);
                    static elrond::pointer<elrond::interface::Stream> makeNullStream();
            };

            class ConsoleStreamAdapter : public elrond::interface::ConsoleStreamAdapter
            {
                protected:
                    ConsoleAdapter* _adapter;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(ConsoleStreamAdapter, =delete, =delete, =delete, =delete, =delete)
                    ConsoleStreamAdapter(ConsoleAdapter& adapter);

                    void flush(elrond::interface::Stream& stream, elrond::SEVERITY severity) override;
                    elrond::pointer<elrond::interface::Stream> makeStream() const override;
            };
        }
    }

#endif
