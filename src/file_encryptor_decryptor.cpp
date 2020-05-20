#include "../include/file_encryptor_decryptor.hpp"

#include <iostream> // std::cerr

namespace my
{
    /**
     * Default constructor
     * Do nothing
    */
    FileEncryptorDecryptor::FileEncryptorDecryptor() noexcept
    {}



    /**
     * @brief Constructor with parameter, set name of the target file which will be encrypted or decrypted
     * 
     * @param target_filename - target file name
    */
    FileEncryptorDecryptor::FileEncryptorDecryptor(const std::string& target_filename) noexcept
        : m_target_file_name {target_filename}
    {}



    /**
     * Default destructor
     * Do nothing
    */
    FileEncryptorDecryptor::~FileEncryptorDecryptor() noexcept
    {}



    /**
     * @brief Set name of the target file which will be encrypted or decrypted
     * 
     * @param new_target_filename - name of the target file
    */
    void FileEncryptorDecryptor::set_target_filename(const std::string& new_target_filename) noexcept
    { m_target_file_name = new_target_filename; }



    /**
     * @brief Encrypt the target file using base and 'salt' keys
     * 
     * @param base_key - Base encryption key
     * @param salt_key - "Salt" encryption key
     * 
     * TODO:
     * Try to open the target file stream:
     * If file stream was opened successfully:
     *      1) read buffer from file and write to 'old_file_buffer',
     *      2) encrypt all characters from buffer and add them to new buffer
     *      3) write new buffer to the file stream
     *      4) close file stream and reset buffer
     * else - print error message to stdout and exit (terminate process) with code 1
    */
    void FileEncryptorDecryptor::encrypt(const uint64_t base_key, const uint32_t salt_key) noexcept
    {
        m_in_out_file_stream.open(m_target_file_name);

        if (m_in_out_file_stream.is_open()) {
            std::string new_file_buffer; // New buffer
            std::string old_file_buffer {std::istreambuf_iterator<char>(m_in_out_file_stream), // Reading buffer from file stream
                                        std::istreambuf_iterator<char>()};

            // Encrypting
            for (char chr : old_file_buffer) {
                chr ^= base_key; // Encrypt the character with a base key
                chr ^= salt_key; // Encrypt the character with a 'salt' key
                new_file_buffer += chr; // Add encrypted character to the new buffer
            }

            m_in_out_file_stream.seekp(0); // Set the current write position on begin of file stream
            m_in_out_file_stream << new_file_buffer; // Write new buffer to file stream
            m_in_out_file_stream.close(); // Close file stream and reset buffer
        }
        else { // If the file stream was not opened
            std::cerr << colors::red << "[-] " << colors::none << "Error: could not open file: " << m_target_file_name << "\n";
            exit(1);
        }
    }



    /**
     * @brief Decrypt the target file using base and 'salt' keys
     * 
     * @param base_key - Base decryption key
     * @param salt_key - "Salt" decryption key
     * 
     * TODO:
     * Try to open the target file stream:
     * If file stream was opened successfully:
     *      1) read buffer from file and write to 'old_file_buffer',
     *      2) decrypt all characters from buffer and add them to new buffer
     *      3) write new buffer to the file stream
     *      4) close file stream and reset buffer
     * else - print error message to stdout and exit (terminate process) with code 1
    */
    void FileEncryptorDecryptor::decrypt(const uint64_t base_key, const uint32_t salt_key) noexcept
    {
        m_in_out_file_stream.open(m_target_file_name);

        if (m_in_out_file_stream.is_open()) {
            std::string new_file_buffer;
            std::string old_file_buffer {std::istreambuf_iterator<char>(m_in_out_file_stream),
                                        std::istreambuf_iterator<char>()};

            // Decrypting
            for (char chr : old_file_buffer) {
                chr ^= salt_key; // Decrypt the character with a 'salt' key
                chr ^= base_key; // Decrypt the character with a base key
                new_file_buffer += chr; // Add decrypted character to the new buffer
            }

            m_in_out_file_stream.seekp(0);
            m_in_out_file_stream << new_file_buffer;
            m_in_out_file_stream.close();
        }
        else {
            std::cerr << colors::red << "[-] " << colors::none << "Error: could not open file: " << m_target_file_name << "\n";
            exit(1);
        }
    }
} // namespace my
