#if !defined  _ELROND_INTERFACE_CHANNEL_HPP
#define _ELROND_INTERFACE_CHANNEL_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace interface {

            class Channel {

                protected:

                    elrond::sizeT _ch = 0;
                    elrond::word _data = LOW_VALUE;

                public:

                    elrond::sizeT const& ch;
                    elrond::word const& data;

                    Channel();

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Channel();
                    #endif
            };
        }
    }

#endif
