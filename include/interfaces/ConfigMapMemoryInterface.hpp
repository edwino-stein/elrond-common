#if !defined  _ELROND_CONFIG_MAP_MEMORY_INTERFACE_HPP
#define _ELROND_CONFIG_MAP_MEMORY_INTERFACE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interfaces {

            class ConfigMapMemoryInterface {
                public:
                    virtual bool alloc(const elrond::sizeT length)=0;
                    virtual bool write(const elrond::byte data)=0;
                    virtual bool read(const elrond::sizeT index, elrond::byte &data) const =0;
            };
        }
    }

#endif
