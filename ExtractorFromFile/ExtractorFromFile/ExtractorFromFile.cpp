// ExtractorFromFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <string>
#include <filesystem>
#include <fstream>

struct Arguments {
    std::string inputFilePath = "";
    std::string outputFilePath = "";
    uintmax_t startPosition = 0;
    uintmax_t fragmentSize = 0;
    std::ifstream inputFile;
    std::ofstream outputFile;
};

std::string BuildFullPath(const std::string& relativePath)
{
	std::string globalPath = std::filesystem::current_path().string() + "\\" + relativePath;
    return globalPath;
}

Arguments GetInput(int argc, char* argv[]) {
    if (argc != 5) {
        throw std::runtime_error(
            "Not enough arguments provided. Please provide 4 arguments.\n"
            "The signature of this func is \n"
            "extract.exe <input file> <output file> <start position> <fragment size>\n"
        );
    }

    Arguments args;

    args.inputFilePath = BuildFullPath(".\\" + static_cast<std::string>(argv[1]));
    args.outputFilePath = BuildFullPath(".\\" + static_cast<std::string>(argv[2]));
    args.startPosition = std::stoi(argv[3]);
    args.fragmentSize = std::stoi(argv[4]);

    args.inputFile.open(args.inputFilePath, std::ios::binary);
    args.outputFile.open(args.outputFilePath, std::ios::binary);

    if (!args.inputFile.is_open() || !args.outputFile.is_open()) {
        throw std::runtime_error(
            "Failed to open input file: " + args.inputFilePath + '\n' +
            "or failed to open output file: " + args.outputFilePath + '\n'
        );
    }

    if (args.startPosition < 0 || args.fragmentSize < 0) {
        throw std::runtime_error("Start position and fragment size must be non-negative integers.\n");
    }

    uintmax_t file_size = std::filesystem::file_size(args.inputFilePath);
    std::cout << "File Size: " << file_size << std::endl;

    if (args.startPosition + args.fragmentSize > file_size) {
        throw std::runtime_error("Start position and fragment size exceed the input file size.\n");
    }

    args.inputFile.seekg(args.startPosition, std::ios::beg);
    return args;
}

void ExtractBytes(Arguments& args) {
    int byte;
    while (args.fragmentSize > 0 && (byte = args.inputFile.get()) != EOF) {
        args.outputFile.put(static_cast<char>(byte));
        --args.fragmentSize;
    }
}

int main(int argc, char* argv[])
{
    try {
        auto args = GetInput(argc, argv);
        ExtractBytes(args);
    }

    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
	}
}