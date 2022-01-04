#if !defined  _ELROND_BASE_CHANNEL_HPP
#define _ELROND_BASE_CHANNEL_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace channel {

            class BaseChannel {

                protected:

                    elrond::uInt8 _ch = 0;
                    elrond::word _data = elrond::low;

                public:

                    elrond::uInt16 ch() const;
                    elrond::word data() const;
            };
        }
    }

#endif
