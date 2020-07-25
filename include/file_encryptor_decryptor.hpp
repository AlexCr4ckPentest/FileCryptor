#include <string>
#include <fstream>

#include "colors.hpp"

#ifndef _FILE_ENCRYPTOR_DECRYPTOR_HPP_
#define _FILE_ENCRYPTOR_DECRYPTOR_HPP_

namespace alex
{
    /**
     * @class FileEncryptorDecryptor
     * 
     * @brief Simple file encryptor and decryptor class
    */
    class FileEncryptorDecryptor
    {
    public:
        FileEncryptorDecryptor() noexcept;
        FileEncryptorDecryptor(const std::string& target_filename) noexcept;

        FileEncryptorDecryptor(const FileEncryptorDecryptor&) = delete;
        FileEncryptorDecryptor& operator=(const FileEncryptorDecryptor&) = delete;

        ~FileEncryptorDecryptor() noexcept;

        inline void set_target_filename(const std::string& new_target_filename) noexcept
        { m_target_file_name = new_target_filename; }

        void encrypt(const uint64_t base_key, const uint32_t salt_key) noexcept;
        void decrypt(const uint64_t base_key, const uint32_t salt_key) noexcept;

    private:
        std::string m_target_file_name;
        std::fstream m_in_out_file_stream;
    }; 
} // namespace alex

#endif // _FILE_ENCRYPTOR_DECRYPTOR_HPP_
