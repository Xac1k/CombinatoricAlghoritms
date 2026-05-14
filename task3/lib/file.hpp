#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <string>
#include <filesystem>
#include <variant>
#include <concepts>
#include <vector>
#include <algorithm>

std::string BuildPath(std::string path, int levelsUp = 0) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path targetPath = currentPath;

    for (int i = 0; i < levelsUp; i++) {
        targetPath = targetPath.parent_path();
    }

    targetPath /= path;
    return targetPath.string();
}

template <typename FileType>
    requires std::same_as<FileType, std::ifstream> || std::same_as<FileType, std::ofstream>
void OpenFile(std::string rpath, FileType& file, int levelsUp = 0) {
    auto gpath = BuildPath(rpath, levelsUp);
    file.open(gpath);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file with path:" + gpath + "\n");
    }
}

