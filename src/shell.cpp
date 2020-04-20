#include "../include/shell.hpp"

namespace Cryptor
{
    static constexpr size_t salt_length = 4;

    Shell::Shell(int argc, char **argv)
        : m_argc {argc}
        , m_argv {argv}
        , opt_desc {"Available options"}
    {
        opt_desc.add_options()
            ("help,h", "show help message")
            ("encrypt,e", "encrypt mode")
            ("decrypt,d", "decrypt mode")
            ("file,f", boost::program_options::value<std::string>(), "set the target file")
        ;
    }

    Shell::~Shell()
    {}

    int Shell::run()
    {
        try {
            boost::program_options::store(boost::program_options::parse_command_line(m_argc, m_argv, opt_desc), opts_map);
            boost::program_options::notify(opts_map);
        }
        catch (boost::program_options::invalid_command_line_syntax &err) {
            std::cerr << Colors::c_red << "[-] " << Colors::c_none << err.what() << "\n";
            return 1;
        }

        if (opts_map.count("help") || opts_map.size() < 2) {
            std::cout << opt_desc << "\n";
            return 0;
        }

        if (opts_map.count("encrypt")) {
            uint64_t encrypt_key = RandomKeyGen::generate_code();
            uint32_t salt = RandomKeyGen::generate_code(salt_length);

            file_encryptor_decryptor.set_file_name(opts_map["file"].as<std::string>());
            return file_encryptor_decryptor.encrypt_file(encrypt_key, salt);
        }
        else if (opts_map.count("decrypt")) {
            uint64_t decrypt_key;
            uint32_t salt;
            std::cout << Colors::c_blue << "[=>] " << Colors::c_none << "Enter decrypt key > ";
            std::cin >> decrypt_key;
            std::cout << Colors::c_blue << "[=>] " << Colors::c_none << "Enter salt key > ";
            std::cin.ignore();
            std::cin >> salt;

            file_encryptor_decryptor.set_file_name(opts_map["file"].as<std::string>());
            return file_encryptor_decryptor.decrypt_file(decrypt_key, salt);
        }
    }
} // namespace Cryptor
