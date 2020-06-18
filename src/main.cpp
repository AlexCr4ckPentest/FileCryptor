// Standart libraries headers
#include <iostream>

// Boost libraries headers
#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp> // boost::filesystem::exists(), boost::filesystem::absolute()

// User headers
#include "../include/colors.hpp"
#include "../include/key_generator.hpp"
#include "../include/file_encryptor_decryptor.hpp"
#include "../include/json_reader.hpp"
#include "../include/json_writer.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace clr = my::colors;

#define DEFAULT_KEY_LENGTH      4   // Default base key length
#define KEY_LENGTH_MIN          2   // Min base key length
#define KEY_LENGTH_MAX          16  // Max base key length

inline void create_key_file_and_write_json(my::JsonWriter& j_writer) noexcept;

int main(int argc, char** argv)
{
    uint16_t key_length;
    std::string key_file_name;

    my::KeyGenerator key_pair_generator;
    my::JsonReader json_file_reader;
    my::JsonWriter json_file_writer;
    my::FileEncryptorDecryptor file_encryptor_decryptor;

    po::variables_map parsed_options;
    po::options_description available_options("Available options");

    available_options.add_options()
        ("help,h", "Show help")
        ("encrypt,e", po::value<std::string>(), "File to encrypt")
        ("decrypt,d", po::value<std::string>(), "File to decrypt")
        ("out-key-file,o", po::value<std::string>(), "Output key file (json)")
        ("in-key-file,i", po::value<std::string>(), "Input key file (json)")
        ("key-length,l", po::value<uint16_t>(&key_length)->default_value(DEFAULT_KEY_LENGTH), "Key length")
    ;

    try {
        po::store(po::parse_command_line(argc, argv, available_options), parsed_options);
        po::notify(parsed_options);
    }
    catch (const po::error& err) {
        std::cerr << clr::red << "[-] " << clr::none << "Error: " << err.what() << "\n";
        return 1;
    }

    if (parsed_options.size() < 2 || parsed_options.count("help")) {
        std::cout << available_options;
        return 0;
    }
    else if (key_length < KEY_LENGTH_MIN || key_length > KEY_LENGTH_MAX) {
        std::cout << clr::red << "[-] " << clr::none << "Error: key length is short or long!\n";
        return 1;
    }

    if (parsed_options.count("out-key-file")) {
        key_file_name = parsed_options["out-key-file"].as<std::string>();
    }
    else if (parsed_options.count("in-key-file")) {
        key_file_name = parsed_options["in-key-file"].as<std::string>();
    }

    json_file_writer.set_filename(key_file_name);
    json_file_reader.set_filename(key_file_name);

    if (!fs::exists(key_file_name)) {
        create_key_file_and_write_json(json_file_writer);
    }

    auto json_obj = json_file_reader.read();

    if (parsed_options.count("encrypt")) {
        auto target_filename {fs::absolute(parsed_options["encrypt"].as<std::string>()).string()};

        if (!fs::exists(target_filename)) {
            std::cerr << clr::red << "[-] " << clr::none << "Error: could not open file: " << target_filename << "\n";
            return 1;
        }

        if (!json_obj["filename"].is_null()) {
            if (json_obj["filename"] != target_filename || json_obj["encrypted"]) {
                std::cerr << clr::red << "[-] " << clr::none << "Error: different files encrypted or this file already encrypted!\n";
                return 1;
            }
        }

        const auto [base_key, salt_key] = key_pair_generator.generate(key_length);

        file_encryptor_decryptor.set_target_filename(target_filename);
        file_encryptor_decryptor.encrypt(base_key, salt_key);

        json_obj["encrypted"] = true;
        json_obj["filename"] = target_filename;
        json_obj["base_key"] = base_key;
        json_obj["salt_key"] = salt_key;

        json_file_writer.write(json_obj);

        std::cout << clr::green << "[+] " << clr::none << "Success: file has been encrypted: " << target_filename << "\n";
        std::cout << clr::green << "[+] " << clr::none << "Success: keys are saved in file: " << key_file_name << "\n";
    }
    else if (parsed_options.count("decrypt")) {
        auto target_filename {fs::absolute(parsed_options["decrypt"].as<std::string>()).string()};

        if (!fs::exists(target_filename)) {
            std::cerr << clr::red << "[-] " << clr::none << "Error: could not open file: " << target_filename << "\n";
            return 1;
        }

        if (json_obj["filename"] != target_filename || (!json_obj["encrypted"])) {
            std::cerr << clr::red << "[-] " << clr::none << "Error: different files encrypted or this file already decrypted!\n";
            return 1;
        }

        const uint64_t base_key {json_obj["base_key"]};
        const uint32_t salt_key {json_obj["salt_key"]};

        file_encryptor_decryptor.set_target_filename(target_filename);
        file_encryptor_decryptor.decrypt(base_key, salt_key);

        json_obj["encrypted"] = false;

        json_file_writer.write(json_obj);

        std::cout << clr::green << "[+] " << clr::none << "Success: file has been decrypted: " << target_filename << "\n";
    }

    return 0;
}

/// Create the key-file and write json template
inline void create_key_file_and_write_json(my::JsonWriter& j_writer) noexcept
{
    j_writer.write(R"(
        {
            "encrypted": false,
            "filename": null,
            "base_key": null,
            "salt_key": null
        }
    )"_json);
}
