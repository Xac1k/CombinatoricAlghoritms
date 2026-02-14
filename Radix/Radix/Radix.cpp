// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <string>
#include <filesystem>
#include <fstream>
#include "Parser.hpp"

constexpr int MIN_BASE = 2;
constexpr int MAX_BASE = 36;

struct Arguments {
    int sourceBase = 0;
    int destinationBase = 0;
    int decimalValue = 0;
};

bool CheckLimit(int val) {
    return val < MIN_BASE || val > MAX_BASE;
}

Arguments GetInputs(int argc, char* argv[]) {
    if (argc < 4) {
        throw std::runtime_error(
            "Not enough arguments provided. Please provide at least 3 argument.\n"
            "The signature of this func is \n"
            "radix.exe <source notation> <destination notation> <value>\n"
        );
    }

    Arguments args;

    args.sourceBase = StringToInt(argv[1], 10);
    args.destinationBase = StringToInt(argv[2], 10);

    if (CheckLimit(args.sourceBase) || CheckLimit(args.destinationBase)) {
        throw std::runtime_error("Source and Destination notation must be between 2 and 36.\n");
    }
    args.decimalValue = StringToInt(argv[3], args.sourceBase);

    return args;
}

//TODO: MIN_INT
int main(int argc, char* argv[])
{
    try {
        auto args = GetInputs(argc, argv);
        std::string result = IntToString(args.decimalValue, args.destinationBase);
		std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what();
        return 1;
	}
}