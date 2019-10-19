#if !defined  _ELROND_CONFIG_MAP_ALLOCATOR_HPP
    #define _ELROND_CONFIG_MAP_ALLOCATOR_HPP

    #include "types.hpp"
    #include "runtime/config/ConfigMap.hpp"

    namespace elrond {
        namespace config {

            class ConfigMapAllocator : public elrond::config::ConfigMap {

                protected:
                    void write(elrond::byte data);
                    void write(const char *key);

                public:

                    ConfigMapAllocator(elrond::interfaces::ConfigMapMemoryInterface &dm);

                    void push(const char *key, int value);
                    void push(const char *key, bool value);
                    void push(const char *key, double value);
                    void push(const char *key, char value);
                    void push(const char *key, const char *value);
            };
        }
    }
#endif
