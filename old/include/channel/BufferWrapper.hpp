#if !defined  _ELROND_BUFFER_WRAPPER_HPP
#define _ELROND_BUFFER_WRAPPER_HPP

    #include "elrond_ext_types.hpp"

    namespace elrond {
        namespace channel {

            class BufferWrapper : public elrond::TaskContext {

                public:

                    elrond::byte* const data;
                    const elrond::sizeT length;

                    BufferWrapper(elrond::byte* const data, const elrond::sizeT length);
            };
        }
    }

#endif
