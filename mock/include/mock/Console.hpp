#ifndef ELROND_MOCK_CONSOLE_HPP
    #define ELROND_MOCK_CONSOLE_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class Console : public elrond::runtime::BaseConsole
            {
                protected:

                    elrond::procedure<elrond::StreamH> printInfoH;
                    void printInfo(const elrond::StreamH& handle) const override;
                    
                public:
                    Console();
                    Console(const elrond::procedure<elrond::StreamH>& printInfoH);
            };
        }
    }

#endif
