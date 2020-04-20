#pragma once

#include <fstream>
#include <sstream>

#include "colors.hpp"

namespace Cryptor
{
    class FileEncryptorDecryptor
    {
    private:
        std::string m_filename;
        std::fstream file_stream;
        std::ostringstream osstream;

    public:
        FileEncryptorDecryptor();

        void set_file_name(std::string filename);
        int encrypt_file(uint64_t encrypt_key, uint32_t salt);
        int decrypt_file(uint64_t decrypt_key, uint32_t salt);
    };
}
