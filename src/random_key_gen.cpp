#include <iostream>
#include <sstream>

#include "../include/random_key_gen.hpp"

namespace Cryptor
{
    std::random_device RandomKeyGen::rand_device;
    std::mt19937 RandomKeyGen::mt{rand_device()};
    std::uniform_int_distribution<> RandomKeyGen::rand_int_generator {1, 9};

    uint64_t RandomKeyGen::generate_code(const size_t key_length)
    {
        std::stringstream buff;

        for (size_t i = 0; i < key_length; i++) {
            buff << rand_int_generator(mt);
        }

        return std::stoul(buff.str());
    }
}
