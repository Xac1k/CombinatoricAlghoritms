// rle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <exception>
#include <filesystem>

std::string helpText = R"(
========NAME========
rle - compress or decompress files using Run-Length Encoding algorithm

======SYNOPSIS======
rle pack <input file> <output file>
rle unpack <input file> <output file>

====DESCRIPTION=====
rle performs Run-Length Encoding compression on binary files with sparse 
content and decompresses files previously packed with this utility.

Compression principle:
When a sequence of identical bytes is detected, it is encoded using two bytes:
the first byte stores the count of repetitions, followed by the actual byte value.

For example, the byte sequence AAABBBBC (8 bytes) is encoded as:
3, 'A', 4, 'B', 1, 'C' (6 bytes)

======OPTIONS=======
pack              Compress input file using RLE algorithm
unpack            Decompress RLE-compressed file

=======NOTES========
• Files of zero length are represented as zero-length output files
• Sequences longer than 255 identical bytes are split into multiple 
  255-byte chunks followed by the remainder
• Single-byte sequences actually require twice the storage space 
  (2 bytes instead of 1)
• This implementation is designed for educational purposes to demonstrate 
  file I/O operations

======EXAMPLES======
rle pack document.bin document.rle
rle unpack document.rle document.bin

====EXIT_STATUS=====
0    Success
1    General error (invalid arguments, file access issues, etc.)

=======AUTHOR=======
Written as educational task.
)";

enum class Mode { Pack, UnPack };
enum class Expectation { Count, Char };
#define MODE 0 // 0-Release, 1-Debug

struct Arguments
{
    Mode mode = Mode::Pack;
    std::ifstream iFile;
    std::ofstream oFile;
};

std::string BuildPath(std::string path, int levelsUp = 0) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path targetPath = currentPath;

    for (int i = 0; i < levelsUp; i++) {
        targetPath = targetPath.parent_path();
    }

    targetPath /= path;
    return targetPath.string();
}

std::shared_ptr<Arguments> GetInput(int argc, char* argv[]) {
    #if MODE == 0
    if (argc == 2) {
        std::string secondParam = static_cast<std::string>(argv[1]);
        if (secondParam == "-h") {
            std::cout << helpText;
            exit(0);
        }
    }
    else if (argc == 4) {
        
            std::string mode = static_cast<std::string>(argv[1]);
            std::string inputPath = static_cast<std::string>(argv[2]);
            std::string outputPath = static_cast<std::string>(argv[3]);
    #endif // MODE == 0

        #if MODE == 1
            std::string mode = static_cast<std::string>("unpack");
            std::string inputPath = static_cast<std::string>("test.bin");
            std::string outputPath = static_cast<std::string>("test.exe");
        #endif // MODE == 1
        

        auto arg = std::make_shared<Arguments>();
        if (mode == "pack") arg->mode = Mode::Pack;
        else if (mode == "unpack") arg->mode = Mode::UnPack;
        else throw std::runtime_error("Unrecognized mode. Please check your enter.\n");

        arg->iFile.open(BuildPath(inputPath), std::ios::binary);
        if (!arg->iFile.is_open()) throw std::runtime_error("Couldn't open the input file: " + inputPath);

        if (arg->mode == Mode::UnPack && std::filesystem::file_size(BuildPath(inputPath)) % 2 != 0) 
            throw std::runtime_error("Uncorrect size of input file for decoding.\n");

        arg->oFile.open(BuildPath(outputPath), std::ios::binary);
        if (!arg->oFile.is_open()) throw std::runtime_error("Couldn't open the output file: " + outputPath);

        arg->iFile.seekg(0, std::ios::beg);
        return arg;
    #if MODE == 0
    }
    else throw std::runtime_error("The Signature of Func isn't correct. For info please enter -h after utils\n");
    #endif // MODE == 0

    
}

void PutRecord(std::ofstream& out, int count, int byte) {
    if (byte == EOF) return;
    if (count <= 0) return;

    out.put(static_cast<unsigned char>(count));
    out.put(static_cast<unsigned char>(byte));
}

void Encode(std::shared_ptr<Arguments> arg) {
    int pByte = arg->iFile.get();
    if (pByte == EOF) return;

    int byte = 0;
    int counter = 1;
    while ((byte = arg->iFile.get()) != EOF) {
        if (pByte == byte) {
            counter++;
            if (counter == 255) {
                PutRecord(arg->oFile, counter, byte);

                counter = 0;
                pByte = arg->iFile.get();
                if (pByte == EOF) break;
                counter = 1;
            }
        }
        else {
            PutRecord(arg->oFile, counter, pByte);
            pByte = byte;
            counter = 1;
        }
    }

    if (counter > 0) PutRecord(arg->oFile, counter, pByte);
}

void Decode(std::shared_ptr<Arguments> arg) {
    arg->iFile.seekg(0, std::ios::end);
    size_t fileSize = static_cast<size_t>(arg->iFile.tellg());
    arg->iFile.seekg(0, std::ios::beg);

    if (fileSize % 2 != 0) 
        throw std::runtime_error("The Format of file doesn't match packed rle format\n");

    unsigned char count = 0;
    unsigned char byte = 0;

    while (arg->iFile.read(reinterpret_cast<char*>(&count), 1) &&
        arg->iFile.read(reinterpret_cast<char*>(&byte), 1)) {
        if (arg->iFile.gcount() != 1)
            throw std::runtime_error("Unexpected end of file while reading RLE pair");
        for (int i = 0; i < count; i++) arg->oFile.put(static_cast<char>(byte));
    }

    if (arg->iFile.bad()) 
        throw std::runtime_error("Error reading input file");
}

int main(int argc, char * argv[])
{
    try {
        auto arg = GetInput(argc, argv);
        if (arg->mode == Mode::Pack) Encode(arg);
        else if (arg->mode == Mode::UnPack) Decode(arg);
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}