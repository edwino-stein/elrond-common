#include <iostream>
#include <random>

extern "C" void concat(std::string& left, const std::string& right)
{
    left += right;
}

extern "C" unsigned int getRandom(const unsigned int min, const unsigned int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}
