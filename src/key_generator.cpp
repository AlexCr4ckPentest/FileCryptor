#include "../include/key_generator.hpp"

namespace my
{
    /// Default constructor
    /// Initialize random engine and random integer generator
    KeyGenerator::KeyGenerator() noexcept
        : rand_device {}
        , mt {rand_device()}
        , get_rand_int {1, 9}
    {}



    /// Default destructor
    /// Do nothing
    KeyGenerator::~KeyGenerator() noexcept
    {}



    /**
     * @brief Generate two keys and returns them
     * 
     * @param key_length  - Length of the base key
     * @param salt_length - Length of the "salt" key (=4 by default)
     * 
     * @return std::pair<> of base key and "salt" key
    */
    std::pair<uint64_t, uint32_t> KeyGenerator::generate(const uint16_t key_length, const uint16_t salt_length) noexcept
    {
        return {generate_key(key_length), generate_key(salt_length)};
    }



    /**
     * @brief Generate one key and returns them
     * 
     * @param key_length - Length of the key
     * 
     * @return generated key
    */
    uint64_t KeyGenerator::generate_key(const uint16_t key_length) noexcept
    {
        buffer.str(""); // Clear buffer

        for (uint16_t i {0}; i < key_length; i++) {
            buffer << get_rand_int(mt);
        }

        return std::stoul(buffer.str()); // Converting std::string to unsigned long
    }
} // namespace my
