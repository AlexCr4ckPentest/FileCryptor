#pragma once

#include <random>

namespace Cryptor
{
    class RandomKeyGen
    {
    private:
        static std::random_device rand_device;
        static std::mt19937 mt;
        static std::uniform_int_distribution<> rand_int_generator;

    public:
        static uint64_t generate_code(const size_t key_length);
    };
} // namesapce Cryptor
