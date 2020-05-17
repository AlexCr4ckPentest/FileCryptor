#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "colors.hpp"
#include "random_key_gen.hpp"
#include "file_ec_dc.hpp"

namespace Cryptor
{
    namespace po = boost::program_options;
    class Shell
    {
    private:
        char **m_argv; int m_argc;
        po::options_description opt_desc;
        po::variables_map opts_map;
        FileEncryptorDecryptor file_encryptor_decryptor;
    public:
        Shell(int argc, char **argv) noexcept;
        Shell(const Shell&) = delete;
        ~Shell() noexcept;
        int run() noexcept;
    };
} // namesapce Cryptor
