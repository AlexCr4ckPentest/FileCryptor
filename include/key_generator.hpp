#include <random>
#include <sstream> // For std::stringstream

#ifndef _KEY_GENERATOR_HPP_
#define _KEY_GENERATOR_HPP_

namespace my
{
    class KeyGenerator
    {
    public:
        explicit KeyGenerator() noexcept;
        KeyGenerator(const KeyGenerator&) = delete;
        KeyGenerator& operator=(const KeyGenerator&) = delete;
        ~KeyGenerator() noexcept;

        std::pair<uint64_t, uint32_t> generate(const uint16_t key_length, const uint16_t salt_length = 4) noexcept;

    private:
        std::random_device rand_device;
        std::mt19937 mt;
        std::uniform_int_distribution<> get_rand_int;
        std::stringstream buffer;

        uint64_t generate_key(const uint16_t key_length) noexcept;
    };
} // namespace my

#endif // _KEY_GENERATOR_HPP_