#include <iostream>
#include <boost/format.hpp>

#include "../include/file_ec_dc.hpp"

namespace Cryptor
{
    FileEncryptorDecryptor::FileEncryptorDecryptor()
    {}

    int FileEncryptorDecryptor::encrypt_file(std::string filename, uint64_t encrypt_key, uint32_t salt)
    {
        file_stream.open(filename, std::ios::in);
        if (!file_stream.is_open()) {
            std::cerr << Colors::c_red << "[-] " << Colors::c_none
                      << boost::format("Could not open file: %1%\n") % filename;
            return 1;
        }

        std::string buff;
        osstream << file_stream.rdbuf();
        file_stream.close();

        for (char ch : osstream.str()) {
            ch ^= encrypt_key;
            ch ^= salt;
            buff += ch;
        }

        file_stream.open(filename, std::ios::out);
        file_stream << buff;
        file_stream.close();
        osstream.str("");

        std::cout << Colors::c_green << "[+] " << Colors::c_none << boost::format("File encrypted: %1%\n") % filename;
        std::cout << Colors::c_yellow << "[!] " << Colors::c_none << boost::format("Your decrypt key is: %1%\n") % encrypt_key;
        std::cout << Colors::c_yellow << "[!] " << Colors::c_none << boost::format("Your salt key is: %u\n") % salt;
        std::cout << Colors::c_yellow << "[!] " << Colors::c_none << boost::format("ATTENTION: save the keys until file decrypt\n");
        return 0;
    }

    int FileEncryptorDecryptor::decrypt_file(std::string filename, uint64_t decrypt_key, uint32_t salt)
    {
        file_stream.open(filename, std::ios::in);
        if (!file_stream.is_open()) {
            std::cerr << Colors::c_red << "[-] " << Colors::c_none
                      << boost::format("Error: could not open file '%1%'\n") % filename;
            return 1;
        }
        std::string buff;
        osstream << file_stream.rdbuf();
        file_stream.close();

        for (char ch : osstream.str()) {
            ch ^= salt;
            ch ^= decrypt_key;
            buff += ch;
        }

        file_stream.open(filename, std::ios::out);
        file_stream << buff;
        file_stream.close();
        osstream.str("");

        std::cout << Colors::c_green << "[+] " << Colors::c_none << boost::format("File decrypted: %1%\n") % filename;
        return 0;
    }
}
