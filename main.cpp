#include <iostream>

#include "include/shell.hpp"

int main(int argc, char **argv)
{
    Cryptor::Shell cryptor_shell(argc, argv);

    return cryptor_shell.run();
}
