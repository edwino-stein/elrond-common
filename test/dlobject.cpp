#include <iostream>
#include <random>

#ifdef WINDOWS_DL_API
    #define DL_API_EXPORT   __declspec(dllexport)
#else
    #define DL_API_EXPORT
#endif

extern "C" {
    DL_API_EXPORT void concat(std::string& left, const std::string& right)
    {
        left += right;
    }

    DL_API_EXPORT unsigned int getRandom(const unsigned int min, const unsigned int max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
        return dist(rng);
    }
}
