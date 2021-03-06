#include "../include/json_writer.hpp"

#include <cassert>

namespace alex
{
    /// Default constructor
    /// Do nothing
    JsonWriter::JsonWriter() noexcept
    {}



    /**
     * @brief Constructor with parameter, name of the file to write
     * 
     * @param filename - name of the file to write
    */
    JsonWriter::JsonWriter(const std::string& filename) noexcept
        : m_filename {filename}
    {}



    /// Default destructor
    /// Do nothing
    JsonWriter::~JsonWriter() noexcept
    {} 



    /**
     * @brief Write json data to file
     * 
     * @param json_format_text - json object to write
     * 
     * @details Open file stream for write, write json object to stream, close file stream
    */
    void JsonWriter::write(const nlohmann::json& json_format_text) noexcept
    {
        m_out_file_stream.open(m_filename);

        assert(m_out_file_stream.is_open());

        m_out_file_stream << json_format_text.dump(4);

        m_out_file_stream.close();
    }
} // namespace alex
