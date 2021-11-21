#ifndef ELROND_CATCH2_HPP
    #define ELROND_CATCH2_HPP
    #include <catch2/catch.hpp>

    template<typename Base, typename T>
    inline bool instanceof(const T*) {
        return std::is_base_of<Base, T>::value;
    }

    template<typename Base, typename T>
    inline bool instanceof(const T&) {
        return std::is_base_of<Base, T>::value;
    }

#endif
