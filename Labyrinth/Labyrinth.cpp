// Labyrinth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <tuple>
#include <filesystem>
#include <fstream>
#include <queue>
#include <set>

std::string helpText = R"(
====DESCRIPTION=====
labyrinth - a program that finds one of the shortest possible paths between 
two points in a maze specified in a text file.

======SYNOPSIS======
labyrinth [INPUT_FILE] [OUTPUT_FILE]
labyrinth -h
labyrinth

======OPTIONS=======
INPUT_FILE            file containing the maze description
OUTPUT_FILE           file to save the result
-h, --help            display this help information

====RESTRICTIONS====
• Maximum maze size: 100×100 cells
• Maze does not have to be rectangular

====INPUT_FORMAT====
'A'   - maze start point
'B'   - maze end point
'#'   - wall
' '   - empty space

===OUTPUT_FORMAT====
'A'   - maze start point
'B'   - maze end point
'#'   - wall
'.'   - path from 'A' to 'B'
' '   - empty space

======EXAMPLE=======
labyrinth input.txt output.txt
labyrinth -h

=======AUTHOR=======
Written by Xac1k.
)";

enum class CellType {Space, Impassable, Start, End};
using Labyrinth = std::vector<std::vector<CellType>>;
using LabyrinthAttendence = std::vector<std::vector<int>>;
using StrLabyrinth = std::vector<std::string>;
struct PointI
{
    int x = -1;
    int y = -1; 

    bool operator==(const PointI& other) const {
        return x == other.x && y == other.y;
    }
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

template <typename Stream>
requires std::same_as<Stream, std::istream> || std::same_as<Stream, std::ifstream>

std::tuple<StrLabyrinth, size_t> ReadFromStream(Stream& stream) {
    std::vector<std::string> unNormalizedLabirint ;
    size_t maxLen = 0;
    std::string tempLine;

    while (std::getline(stream, tempLine)) {
        if (unNormalizedLabirint.size() == 100)
            throw std::runtime_error("String overflow. The Labirint cann't to be biger then 100 chart in column\n");

        if (tempLine.size() > 100)
            throw std::runtime_error("String overflow. The Labirint cann't to be biger then 100 chart in row\n");

        unNormalizedLabirint.push_back({ tempLine });
        if (tempLine.size() > maxLen)
            maxLen = tempLine.size();
    }

    return std::make_tuple(unNormalizedLabirint, maxLen);
}

void NormalizeLabirint(StrLabyrinth& unNormalizedLabirint, size_t maxLine) {
    for (auto& line : unNormalizedLabirint) {
        line.resize(maxLine, ' ');
    }
}

Labyrinth Str2CellType(const StrLabyrinth& NormalizedLabirint) {
    std::vector<std::vector<CellType>> Labirint;
    bool haveStart = false;
    bool haveEnd = false;

    for (const auto& line : NormalizedLabirint) {
        Labirint.push_back({});
        for (const auto& ch : line) {
            if (ch == '#') {
                Labirint[Labirint.size() - 1].push_back(CellType::Impassable);
            }
            else if (ch == 'A') {
                if (haveStart)
                    throw std::runtime_error("The Laberint have 2 or more Start points.");
                Labirint[Labirint.size() - 1].push_back(CellType::Start);
                haveStart = true;
            }
            else if (ch == 'B') {
                if (haveEnd)
                    throw std::runtime_error("The Laberint have 2 or more End points.");
                Labirint[Labirint.size() - 1].push_back(CellType::End);
                haveEnd = true;
            }
            else if (ch == ' ') {
                Labirint[Labirint.size() - 1].push_back(CellType::Space);
            }
            else
                throw std::runtime_error("Unrecognized symbol into labirint. Plese check the correctness of you input.\n");
        }
    }

    if (!haveEnd || !haveStart) 
        throw std::runtime_error("The Labyrinth haven't start or end point");

    return Labirint;
}

std::tuple<Labyrinth, std::ostream*> GetInputs(int argc, char* argv[]) {
    if (argc == 1) {
        auto [unNormalizedLabirin, maxLen] = ReadFromStream(std::cin);
        NormalizeLabirint(unNormalizedLabirin, maxLen);
        Labyrinth lab = Str2CellType(unNormalizedLabirin);
        return { lab, &std::cout };
    }
    else if (argc == 2) {
        if (static_cast<std::string>(argv[1]) == "-h") {
            std::cout << helpText;
            exit(0);
        }
    }
    else if (argc == 3) {
        std::ifstream iFile(BuildPath(".\\" + static_cast<std::string>(argv[1])));
        if (!iFile.is_open()) {
            throw std::runtime_error("Couldn't open input file with Path: " + BuildPath(".\\" + static_cast<std::string>(argv[1])));
        }

        static std::ofstream oFile(BuildPath(".\\" + static_cast<std::string>(argv[2])));
        if (!oFile.is_open()) {
            throw std::runtime_error("Couldn't open output file with Path: " + BuildPath(".\\" + static_cast<std::string>(argv[2])));
        }
        
        auto [unNormalizedLabirin, maxLen] = ReadFromStream(iFile);
        NormalizeLabirint(unNormalizedLabirin, maxLen);
        Labyrinth lab = Str2CellType(unNormalizedLabirin);
        return { lab, &oFile };
    }
    else {
        throw std::runtime_error("Unknown signature of func. Add -h to func for help.");
    }
}

std::tuple<PointI, PointI> GetStartAndEndPoint(const Labyrinth& labyrinth) {
    PointI start, end;
    for (int lineID = 0; lineID < labyrinth.size(); lineID++) {
        for (int cellID = 0; cellID < labyrinth[lineID].size(); cellID++) {
            if (labyrinth[lineID][cellID] == CellType::Start) {
                start = { cellID, lineID };
            }
            if (labyrinth[lineID][cellID] == CellType::End) {
                end = { cellID, lineID };
            }
            if (start.x > 0 && end.x > 0) {
                return std::make_tuple(start, end);
            }
        }
    }
    return std::make_tuple(start, end);
}

LabyrinthAttendence GetInitAttendence(const Labyrinth& labyrinth, const PointI& end) {
    if (labyrinth.size() == 0) throw std::runtime_error("There is null labyrinth");
    size_t ySize = labyrinth.size();
    size_t xSize = labyrinth[0].size();

    LabyrinthAttendence attendence;
    attendence.resize(ySize, {});
    for (auto& line : attendence) {
        line.resize(xSize, -1);
    }

    attendence[end.y][end.x] = 0;
    return attendence;
}

bool IsPointOutRange(const PointI& p, const LabyrinthAttendence& attendence) {
    if (!attendence.size()) 
        throw std::runtime_error("There is null attendence list.\n");
    size_t ySize = attendence.size();
    size_t xSize = attendence[0].size();

    return !(p.x >= 0 && p.y >= 0 && p.x < xSize && p.y < ySize);
}

bool IsPointValid(const LabyrinthAttendence& attendence, const Labyrinth& labyrinth, const PointI& point) {
    return !IsPointOutRange(point, attendence) &&
        attendence[point.y][point.x] == -1 &&
        labyrinth[point.y][point.x] == CellType::Space;
}

bool IsPointAdjoinedToPoint(const PointI& target, const PointI& point) {
    return (abs(point.x - target.x) == 1 && abs(point.y - target.y) == 0) ||
        (abs(point.x - target.x) == 0 && abs(point.y - target.y) == 1);
}

void MarkAsVisited(LabyrinthAttendence& attendence, const PointI& nextPoint, const PointI& prevPoint) {
    attendence[nextPoint.y][nextPoint.x] = attendence[prevPoint.y][prevPoint.x] + 1;
}

bool AddTasksByNeimanLocality(std::queue<PointI>& combatList, LabyrinthAttendence& attendence, const Labyrinth& labyrinth, const PointI& currPoint) {
    bool wasChanged = false;
    PointI upPoint = { currPoint.x, currPoint.y - 1 };
    PointI downPoint = { currPoint.x, currPoint.y + 1 };
    PointI leftPoint = { currPoint.x - 1, currPoint.y };
    PointI rightPoint = { currPoint.x + 1, currPoint.y };

    if (IsPointValid(attendence, labyrinth, upPoint)) {
        combatList.push(upPoint);
        MarkAsVisited(attendence, upPoint, currPoint);
        wasChanged = true;
    }
    if (IsPointValid(attendence, labyrinth, downPoint)) {
        combatList.push(downPoint);
        MarkAsVisited(attendence, downPoint, currPoint);
        wasChanged = true;
    }
    if (IsPointValid(attendence, labyrinth, leftPoint)) {
        combatList.push(leftPoint);
        MarkAsVisited(attendence, leftPoint, currPoint);
        wasChanged = true;
    }
    if (IsPointValid(attendence, labyrinth, rightPoint)) {
        combatList.push(rightPoint);
        MarkAsVisited(attendence, rightPoint, currPoint);
        wasChanged = true;
    }

    return wasChanged = true;
}

bool IsPointMoreFar(const LabyrinthAttendence& attendence, const PointI& target, const PointI& org) {
    return (attendence[org.y][org.x] != -1 && attendence[target.y][target.x] == -1) ||
        (attendence[org.y][org.x] != -1 && attendence[target.y][target.x] > attendence[org.y][org.x]);
}

PointI GetNextPointByNSWE(const LabyrinthAttendence& attendence, const PointI& p) {
    PointI northP  = { p.x, p.y - 1 };
    PointI southhP = { p.x, p.y + 1 };
    PointI westP   = { p.x - 1, p.y };
    PointI eastP   = { p.x + 1, p.y };

    if (!IsPointOutRange(northP, attendence) && attendence[northP.y][northP.x] != -1 && !IsPointMoreFar(attendence, northP, p))
        return northP;
    else if (!IsPointOutRange(southhP, attendence) && attendence[southhP.y][southhP.x] != -1 && !IsPointMoreFar(attendence, southhP, p))
        return southhP;
    else if (!IsPointOutRange(westP, attendence) && attendence[westP.y][westP.x] != -1 && !IsPointMoreFar(attendence, westP, p))
        return westP;
    else if (!IsPointOutRange(eastP, attendence) && attendence[eastP.y][eastP.x] != -1 && !IsPointMoreFar(attendence, eastP, p))
        return eastP;

    throw std::runtime_error("The point: (" + std::to_string(p.x) + ":" + std::to_string(p.y) + ") hasn't nearest attended point\n");
}

std::vector<PointI> PathRestore(const LabyrinthAttendence& attendence, const PointI& start, const PointI& end) {
    std::vector<PointI> path;
    PointI location = start;

    while(!IsPointAdjoinedToPoint(end, location)) {
        location = GetNextPointByNSWE(attendence, location);
        path.push_back(location);
    }

    return path;
}

bool PointFind(const std::vector<PointI>& where, const PointI& what) {
    for (auto& point : where) {
        if (what == point) return true;
    }
    return false;
}

std::vector<PointI> SearchPath(const Labyrinth& labyrinth) {
    auto [start, end] = GetStartAndEndPoint(labyrinth);
    auto attendence = GetInitAttendence(labyrinth, end);
    bool PathFound = false; 
    std::queue<PointI> combatList({ end });

    do {
        PointI currPoint = combatList.front();
        combatList.pop();
        PathFound = IsPointAdjoinedToPoint(start, currPoint);
        if(PathFound) break;
        AddTasksByNeimanLocality(combatList, attendence, labyrinth, currPoint);
    } while (!combatList.empty());

    std::vector<PointI> path;
    if (PathFound) {
        path = PathRestore(attendence, start, end);
    }

    return path;
}

void PrintWithPath(const Labyrinth& labyrinth, const std::vector<PointI>& path, std::ostream* out) {
    for (int y = 0; y < labyrinth.size(); y++) {
        for (int x = 0; x < labyrinth[0].size(); x++) {
            switch (labyrinth[y][x]) {
                case CellType::End:
                    *out << "B";
                    break;
                case CellType::Start:
                    *out << "A";
                    break;
                case CellType::Space: {
                    bool isDot = PointFind(path, { x, y });
                    std::string symbol = isDot ? "." : " ";
                    *out << symbol;
                    break;
                } 
                case CellType::Impassable:
                    *out << "#";
                    break;
            }
        }
        *out << std::endl;
    }
}
 
int main(int argc, char* argv[])
{
    try {
        auto [labyrinth, out] = GetInputs(argc, argv);
        auto path = SearchPath(labyrinth);
        PrintWithPath(labyrinth, path, out);
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}