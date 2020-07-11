#include <fstream>

#include "nlohmann/json.hpp"

#ifndef _JSON_READER_HPP_
#define _JSON_READER_HPP_

namespace alex
{
    /**
     * @class JsonReader
     * 
     * @brief Simple json reader class which open file and read data in json format from file
    */
    class JsonReader
    {
    public:
        JsonReader() noexcept;
        JsonReader(const std::string& filename) noexcept;
        JsonReader(const JsonReader&) = delete;
        JsonReader& operator=(const JsonReader&) = delete;
        ~JsonReader() noexcept;

        void set_filename(const std::string& new_filename) noexcept;
        nlohmann::json read() noexcept;
    private:
        std::string m_filename;
        std::ifstream m_in_file_stream;
    };
} // namespace alex

#endif // _JSON_READER_HPP_
