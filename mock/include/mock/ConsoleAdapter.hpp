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
                    using MakeStreamAdapterH = elrond::function<elrond::pointer<elrond::interface::StreamAdapter>, elrond::interface::Stream&, elrond::string>;

                protected:
                    elrond::interface::Stream& _stream;
                    MakeStreamAdapterH _makeStreamAdapter;

                    elrond::pointer<elrond::interface::StreamAdapter>
                    makeStreamAdapter(const elrond::string& severity) const;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(ConsoleAdapter, =delete, =default, =default, =default, =default)

                    ConsoleAdapter(elrond::interface::Stream& stream);
                    ConsoleAdapter(elrond::interface::Stream& stream, MakeStreamAdapterH makeStreamAdapter);

                    elrond::pointer<elrond::interface::StreamAdapter> getInfoStreamAdapter() const override;
                    elrond::pointer<elrond::interface::StreamAdapter> getErrorStreamAdapter() const override;

                    static ConsoleAdapter* null();
            };
        }
    }

#endif
