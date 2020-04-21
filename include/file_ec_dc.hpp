#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include "colors.hpp"

namespace Cryptor
{
    class FileEncryptorDecryptor
    {
    private:
        std::fstream file_stream;
        std::ostringstream osstream;

    public:
        FileEncryptorDecryptor();
        int encrypt_file(std::string filename, uint64_t encrypt_key, uint32_t salt);
        int decrypt_file(std::string filename, uint64_t decrypt_key, uint32_t salt);
    };
}
