#if !defined  _ELROND_CATCH_HPP
    #define _ELROND_CATCH_HPP

    #include "./catch.hpp"

    #define EXPECT_ASSERTS(T) static unsigned int __counter_asserts__ = 0;\
                              static unsigned int __expected_asserts__ = T

    #define ASSERT_N_COUNT(...) __VA_ARGS__; ++__counter_asserts__
    #define CHECK_N_COUNT(...) ASSERT_N_COUNT(CHECK(__VA_ARGS__))
    #define REQUIRE_N_COUNT(...) ASSERT_N_COUNT(REQUIRE(__VA_ARGS__))
    #define REQUIRE_ALL_DONE(M) SECTION(M){ REQUIRE(__counter_asserts__ == __expected_asserts__); }

#endif
