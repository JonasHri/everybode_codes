#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <tuple>

// Custom hash function for tuples
struct TupleHash {
    template <typename T1, typename T2, typename T3>
    size_t operator()(const std::tuple<T1, T2, T3>& tuple) const {
        auto [x, y, z] = tuple;
        return std::hash<T1>{}(x) ^ (std::hash<T2>{}(y) << 1) ^ (std::hash<T3>{}(z) << 2);
    }
};

// 3D Position Struct
struct Vector3D {
    int x, y, z;
    bool visited; 
    Vector3D(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z), visited(false) {}
    void markVisited(){
        this->visited= true; 
    }
};

// Define the unordered_set with custom hash
using Grid = std::unordered_set<std::tuple<int, int, int>, TupleHash>;

void markMap(Grid &grid, Vector3D &pos, char dir, int len);
int countMap(const Grid &grid);
std::vector<std::pair<char, int>> parseInputFile(const std::string &filename);

int main() {
    auto growthPattern = parseInputFile("everybody_codes_e2024_q14_p2.txt");
    if (growthPattern.empty()) {
        std::cerr << "No valid input data." << std::endl;
        return 1;
    }

    Vector3D position;
    Grid visitedCells;

    for (const auto &[dir, len] : growthPattern) {
        markMap(visitedCells, position, dir, len);
    }

    std::cout << "Result: " << countMap(visitedCells) << std::endl;
    return 0;
}

std::vector<std::pair<char, int>> parseInputFile(const std::string &filename) {
    std::vector<std::pair<char, int>> growthPattern;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File not found: " << filename << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string arg;
        while (std::getline(ss, arg, ',')) {
            if (arg.empty()) continue;
            growthPattern.emplace_back(arg[0], std::stoi(arg.substr(1)));
        }
    }
    return growthPattern;
}

void markMap(Grid &grid, Vector3D &pos, char dir, int len) {
    for (int i = 0; i < len; ++i) {
        switch (dir) {
            case 'U': grid.insert({pos.x, pos.y, pos.z + i}); break;
            case 'D': grid.insert({pos.x, pos.y, pos.z - i}); break;
            case 'R': grid.insert({pos.x + i, pos.y, pos.z}); break;
            case 'L': grid.insert({pos.x - i, pos.y, pos.z}); break;
            case 'F': grid.insert({pos.x, pos.y + i, pos.z}); break;
            case 'B': grid.insert({pos.x, pos.y - i, pos.z}); break;
            default: std::cerr << "Invalid instruction: " << dir << std::endl;
        }
    }

    // Update the position after movement
    switch (dir) {
        case 'U': pos.z += len; break;
        case 'D': pos.z -= len; break;
        case 'R': pos.x += len; break;
        case 'L': pos.x -= len; break;
        case 'F': pos.y += len; break;
        case 'B': pos.y -= len; break;
    }
}

int countMap(const Grid &grid) {
    return grid.size();
}
