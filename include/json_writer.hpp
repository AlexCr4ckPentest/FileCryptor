#include <fstream>

#include "nlohmann/json.hpp"

#include "colors.hpp"

#ifndef _JSON_WRITER_HPP_
#define _JSON_WRITER_HPP_

namespace alex
{
    /**
     * @class JsonWriter
     * 
     * @brief Simple json writer class which create file and write data in json format to file
    */
    class JsonWriter
    {
    public:
        JsonWriter() noexcept;
        JsonWriter(const std::string& filename) noexcept;

        JsonWriter(const JsonWriter&) = delete;
        JsonWriter& operator=(const JsonWriter&) = delete;

        ~JsonWriter() noexcept;

        inline void set_filename(const std::string& new_filename) noexcept
        { m_filename = new_filename; }

        void write(const nlohmann::json& json_format_text) noexcept;

    private:
        std::string m_filename;
        std::ofstream m_out_file_stream;
    };
} // namespace alex

#endif // _JSON_WRITER_HPP_
