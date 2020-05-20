#include "../include/json_reader.hpp"

#include <cassert>

namespace my
{
    /// Default constructor
    /// Do nothing
    JsonReader::JsonReader() noexcept
    {}



    /**
     * @brief Constructor with parameter, set name of the file to read
     * 
     * @param filename - name of the file to read
    */
    JsonReader::JsonReader(const std::string& filename) noexcept
        : m_filename {filename}
    {}



    /// Default destructor
    /// Do nothing
    JsonReader::~JsonReader() noexcept
    {}



    /**
     * @brief Set name of the file to read
     * 
     * @param new_filename - name of the file to read
    */
    void JsonReader::set_filename(const std::string& new_filename) noexcept
    { m_filename = new_filename; }


    /**
     * @brief Read json data from file
     * 
     * @return json object
     * 
     * @details Open file stream for read, write data from stream to json object,
     *          close file stream and return json object
    */
    nlohmann::json JsonReader::read() noexcept
    {
        nlohmann::json json_obj;
        m_in_file_stream.open(m_filename);

        assert(m_in_file_stream.is_open());

        m_in_file_stream >> json_obj;
        m_in_file_stream.close();

        assert(!json_obj.is_null());

        return json_obj;
    }
} // namespace my
