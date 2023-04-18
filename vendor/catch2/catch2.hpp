#ifndef ELROND_CATCH2_HPP
    #define ELROND_CATCH2_HPP

    #include <catch2/catch_all.hpp>

    template<typename Base, typename T>
    inline bool isBaseOf(const T*) {
        return std::is_base_of<Base, T>::value;
    }

    template<typename Base, typename T>
    inline bool isBaseOf(const T&) {
        return std::is_base_of<Base, T>::value;
    }

    template<typename Base, typename T>
    inline bool isInstanceOf(T *const o) {
        return dynamic_cast<Base*>(o) != nullptr;
    }

    template<typename Base, typename T>
    inline bool isInstanceOf(const T& o) {
        return dynamic_cast<const Base*>(&o) != nullptr;
    }

#endif
