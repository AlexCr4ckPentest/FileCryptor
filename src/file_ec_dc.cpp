#include <iostream>
#include <boost/format.hpp>

#include "../include/file_ec_dc.hpp"

namespace Cryptor
{
    FileEncryptorDecryptor::FileEncryptorDecryptor()
    {}

    void FileEncryptorDecryptor::set_file_name(std::string filename)
    {
        m_filename = filename;
    }

    void FileEncryptorDecryptor::encrypt_file(uint64_t encrypt_key, uint32_t salt)
    {
        file_stream.open(m_filename, std::ios::in);
        if (!file_stream.is_open()) {
            std::cerr << Colors::c_red << "[-] " << Colors::c_none << boost::format("Could not open file: %1%\n") % m_filename;
            exit(1);
        }

        std::string buff;
        osstream << file_stream.rdbuf();
        file_stream.close();

        for (char ch : osstream.str()) {
            ch ^= encrypt_key;
            ch ^= salt;
            buff += ch;
        }

        file_stream.open(m_filename, std::ios::out);
        file_stream << buff;
        file_stream.close();
        osstream.str("");

        std::cout << Colors::c_green << "[+] " << Colors::c_none << boost::format("File encrypted: %1%\n") % m_filename;
        std::cout << Colors::c_yellow << "[!] " << Colors::c_none << boost::format("Your decrypt key is: %1%\n") % encrypt_key;
        std::cout << Colors::c_yellow << "[!] " << Colors::c_none << boost::format("Your salt key is: %u\n") % salt;
        std::cout << Colors::c_yellow << "[!] " << Colors::c_none << boost::format("ATTENTION: save the keys until file decrypt\n");
    }

    void FileEncryptorDecryptor::decrypt_file(uint64_t decrypt_key, uint32_t salt)
    {
        file_stream.open(m_filename, std::ios::in);
        if (!file_stream.is_open()) {
            std::cerr << Colors::c_red << "[-] " << Colors::c_none << "Error: could not open file!\n";
            exit(1);
        }
        std::string buff;
        osstream << file_stream.rdbuf();
        file_stream.close();

        for (char ch : osstream.str()) {
            ch ^= salt;
            ch ^= decrypt_key;
            buff += ch;
        }

        file_stream.open(m_filename, std::ios::out);
        file_stream << buff;
        file_stream.close();
        osstream.str("");

        std::cout << Colors::c_green << "[+] " << Colors::c_none << boost::format("File decrypted: %1%\n") % m_filename;
    }
}
