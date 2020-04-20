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
    class Shell
    {
    private:
        int m_argc; char **m_argv;

        RandomKeyGen random_key_gen;
        FileEncryptorDecryptor file_encryptor_decryptor;

        boost::program_options::options_description opt_desc;
        boost::program_options::variables_map opts_map;

    public:
        Shell(int argc, char **argv);
        ~Shell();
        int run();
    };
} // namesapce Cryptor
