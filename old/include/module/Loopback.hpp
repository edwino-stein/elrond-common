#if !defined  _ELROND_LOOPBACK_MODULE_HPP
    #define _ELROND_LOOPBACK_MODULE_HPP

    #include "elrond_ext_types.hpp"

    namespace elrond {
        namespace module {

            class Loopback : public elrond::module::BaseDataLinkModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Loopback();
                    #endif

                    bool send(elrond::byte data[], const elrond::sizeT length) override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
