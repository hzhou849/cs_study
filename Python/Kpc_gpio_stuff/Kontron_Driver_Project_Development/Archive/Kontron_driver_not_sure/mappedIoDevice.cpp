// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <iomanip>
#include "MappedIoDevice.h"
#include "MappedMemoryDevice.h"



void print_syntax(std::string name)
{
    std::cout << "Syntax:\n" << name << " read " << " REGISTER\n" << name << " write " << " REGISTER VALUE\n"
    << std::endl;
}

std::uint32_t string_to_number(const std::string & str)
{
    const std::string prefix_hex = "0x";
    const std::string prefix_bin = "0b";
    const std::string prefix = str.substr(0, 2);
    if (prefix == prefix_hex)
    {
        return std::stoul(str.substr(2), nullptr, 16);
    }
    else if (prefix == prefix_bin)
    {
        return std::stoul(str.substr(2), nullptr, 2);
    }
    else
    {
        return std::stoul(str, nullptr, 10);
    }
}

int read_register(const std::string & arg)
{
    const std::uint32_t addr = string_to_number(arg);

    MappedIoDevice <DeviceAccess::READ> device(addr, sizeof(std::uint32_t));

    const auto val = device.read<std::uint32_t>(0);
    std::cout << "0x" << std::setfill('0') << std::hex << std::setw(8) << addr << ":" << std::endl;
    std::cout << "\tDec: " << std::dec << std::setw(0) << val << std::endl;
    std::cout << "\tHex: " << std::hex << std::setw(8) << val << std::endl;
    std::cout << "\tBin:";
    for (int i = 31; i >= 0; i--)
    {
        if ((i + 1) % 4 == 0)
        {
            std::cout << " ";
        }
        std::cout << ((val & (1 << i)) ? "1" : "0");
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

int write_register(const std::string & reg_string, const std::string & val_string)
{
    const std::uint32_t addr = string_to_number(reg_string);
    const std::uint32_t val = string_to_number(val_string);
    std::cout << "write 0x" << std::setfill('0') << std::hex << std::setw(8) << val << " to 0x" << addr << std::endl;
    MappedIoDevice <DeviceAccess::READ_WRITE> device(addr, sizeof(std::uint32_t));
    device.write<std::uint32_t>(0, val);
    if (device.read<std::uint32_t>(0) == val)
    {
        std::cout << "success" << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "failed" << std::endl;
        return EXIT_FAILURE;
    }

}

int main(int argc, char * argv[])
{
    // test compilation
    MappedMemoryDevice <DeviceAccess::READ_WRITE> dummy(0, 1);

    if (argc < 3)
    {
        print_syntax(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string command = argv[1];
    std::vector <std::string> args;
    for (int i = 2; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    if (command == "r" || command == "R" || command == "read")
    {
        for (const auto & arg : args)
        {
            if (read_register(arg) == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }
        }
    }
    else if (command == "w" || command == "W" || command == "write")
    {
        if (args.size() != 2)
        {
            print_syntax(argv[0]);
            return EXIT_FAILURE;
        }
        return write_register(args[0], args[1]);
    }
    else
    {
        print_syntax(argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
