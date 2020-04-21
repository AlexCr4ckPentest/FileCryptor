#include "../include/shell.hpp"

namespace Cryptor
{
    static constexpr size_t salt_length = 4;
    static size_t key_length;

    Shell::Shell(int argc, char **argv)
        : m_argc {argc}
        , m_argv {argv}
        , opt_desc {"Available options"}
    {
        opt_desc.add_options()
            ("help,h", "show help message")
            ("encrypt,e", "encrypt mode")
            ("decrypt,d", "decrypt mode")
            ("key-length,l", boost::program_options::value<size_t>(&key_length)->default_value(4)
                                                            ->notifier(
                                                                [](size_t value)
                                                                {
                                                                    if (value > 16) {
                                                                        std::cerr << Colors::c_red << "[-] " << Colors::c_none << "Key length is large!\n";
                                                                        exit(1);
                                                                    }
                                                                }), "set the key length")
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
            std::cerr << Colors::c_red << "[-] " << Colors::c_none << err.what() << std::endl;
            return 1;
        }

        if (opts_map.count("help") || opts_map.size() < 2) {
            std::cout << opt_desc << std::endl;
            return 0;
        }

        if (opts_map.count("key-length")) {
            key_length = opts_map["key-length"].as<size_t>();
        }

        if (opts_map.count("encrypt")) {
            uint64_t encrypt_key = RandomKeyGen::generate_code(key_length);
            uint32_t salt = RandomKeyGen::generate_code(salt_length);

            file_encryptor_decryptor.set_file_name(opts_map["file"].as<std::string>());
            file_encryptor_decryptor.encrypt_file(encrypt_key, salt);
        }
        else if (opts_map.count("decrypt")) {
            uint64_t decrypt_key;
            uint32_t salt;
            std::cout << Colors::c_blue << "[=>] " << Colors::c_none << "Enter decrypt key > ";
            std::cin >> decrypt_key;
            std::cout << Colors::c_blue << "[=>] " << Colors::c_none << "Enter salt key > ";
            std::cin >> salt;

            file_encryptor_decryptor.set_file_name(opts_map["file"].as<std::string>());
            file_encryptor_decryptor.decrypt_file(decrypt_key, salt);
        }
        return 0;
    }
} // namespace Cryptor
