#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <tuple>
#include <limits>
#include <cmath>
#include <queue>

void makestep(std::tuple<int,int,int>& curr, const std::pair<char, int>& pattern, std::vector<std::vector<std::vector<int>>>& map);
int calcsize(const std::vector<std::vector<std::vector<int>>>& map);
long murkiness(const std::tuple<int,int,int>& pos, const std::tuple<int,int,int>& leaf); 
bool isValid(int x, int y, int z, const std::vector<std::vector<std::vector<int>>>& map);
long findPath(const std::tuple<int, int, int>& start, const std::tuple<int, int, int>& end, 
    const std::vector<std::vector<std::vector<int>>>& map);

namespace std{
    ostream& operator<<(ostream& os, const pair<char, int>& p){
        os << p.first <<", "<<p.second;
        return os;
    }
    ostream& operator<<(ostream& os, const std::vector<std::pair<char, int>>& vp){
        for(const auto p: vp){
            os << p << endl;
        }
        return os; 
    }
    ostream& operator<<(ostream& os, const std::tuple<int,int,int>& t){
        os << get<0>(t) <<", "<< get<1>(t) <<", "<<get<2>(t);
        return os; 
    }
}

int main(){ 
    std::vector<std::vector<std::pair<char, int>>> growthPattern;
    std::ifstream file("everybody_codes_e2024_q14_p3.txt");
    if (!file) {
        std::cerr << "File not found: " << "everybody_codes_e2024_q14_p3.txt" << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string arg;
        std::vector<std::pair<char, int>> currline;
        while (std::getline(ss, arg, ',')) {
            if (arg.empty()) continue;
            currline.emplace_back(arg[0], std::stoi(arg.substr(1)));
        }
        growthPattern.push_back(currline);
    }
    // std::cout << growthPattern; 
    std::vector<std::vector<std::vector<int>>> map(400, std::vector<std::vector<int>>(400, std::vector<int>(400, 0)));

    std::tuple<int,int,int> pos(0,200,200); 
    std::vector<std::tuple<int,int,int>> leafs;
    
    int cnt =1, rowcnt=1; 
    for(auto row: growthPattern){
        std::cout << "on row: "<< rowcnt <<"/"<<growthPattern.size() <<std::endl;
        for(auto pattern: row){
            // std::cout << cnt <<"/"<< row.size()<<" size: " <<pattern.second <<  std::endl; 
            cnt ++; 
            makestep(pos, pattern, map);
        }
        leafs.push_back(pos);    
        // int erg= calcsize(map);
        // std::cout <<erg<<std::endl; ; 
        cnt=1;
        pos={0,200,200}; 
        rowcnt++; 
    }
    // for(const auto& leaf: leafs){
    //     std::cout << leaf<< std::endl;
    // }
    pos={1,200,200}; 
    long murk=std::numeric_limits<int>::max(); 
    for(int i=0; i<400; i++){
        std::cout << "doing height:"<<i <<std::endl; 
        long counter=0; 
        for(const auto leaf: leafs){
            // std::cout<<"murkiness at: "<<pos<<", "<<leaf <<": " << murkiness(pos, leaf)<<std::endl; 
            counter+=findPath(pos, leaf, map);
            // std::cout << leaf<< std::endl; 
        }
        // std::cout << i<<" dist: " <<counter << ", lowest: "<< murk<<std::endl; 
        // std::cout << pos << std::endl; 
        if(counter< murk){
            if(counter <0){
                continue;
            }
            murk=counter;
            // std::cout << "row_ " <<i<<" cnt: "<<counter<< std::endl; 
        }
        std::get<0>(pos) +=1; 
    }
    std::cout << murk <<std::endl; 
    return 0; 
}

struct Node {
    int x, y, z, distance;
};
struct TupleHash {
    size_t operator()(const std::tuple<int, int, int>& t) const {
        auto [x, y, z] = t;
        return std::hash<int>()(x) ^ (std::hash<int>()(y) << 1) ^ (std::hash<int>()(z) << 2);
    }
};


bool isValid(int x, int y, int z, const std::vector<std::vector<std::vector<int>>>& map) {
    return x >= 0 && x < map.size() &&
           y >= 0 && y < map[0].size() &&
           z >= 0 && z < map[0][0].size() &&
           map[x][y][z] == 1; // Only allow movement on tiles marked as 1
}

long findPath(const std::tuple<int, int, int>& start, const std::tuple<int, int, int>& end, 
              const std::vector<std::vector<std::vector<int>>>& map) {
    int sx, sy, sz, ex, ey, ez;
    std::tie(sx, sy, sz) = start;
    std::tie(ex, ey, ez) = end;

    if (!isValid(sx, sy, sz, map) || !isValid(ex, ey, ez, map)) {
        return -1; // No valid path if start or end is blocked
    }

    std::queue<Node> q;
    std::unordered_set<std::tuple<int, int, int>, TupleHash> visited;
    
    q.push({sx, sy, sz, 0});
    visited.insert({sx, sy, sz});

    int directions[6][3] = { {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1} };

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.x == ex && current.y == ey && current.z == ez) {
            return current.distance; // Return the shortest path length
        }

        for (auto& dir : directions) {
            int nx = current.x + dir[0];
            int ny = current.y + dir[1];
            int nz = current.z + dir[2];

            if (isValid(nx, ny, nz, map) && visited.find({nx, ny, nz}) == visited.end()) {
                q.push({nx, ny, nz, current.distance + 1});
                visited.insert({nx, ny, nz});
            }
        }
    }

    return -1; // No path found
}

long murkiness(const std::tuple<int, int, int>& pos, const std::tuple<int, int, int>& leaf) {
    return std::abs(std::get<0>(pos) - std::get<0>(leaf)) +
           std::abs(std::get<1>(pos) - std::get<1>(leaf)) +
           std::abs(std::get<2>(pos) - std::get<2>(leaf));
}

int calcsize(const std::vector<std::vector<std::vector<int>>>& map){
    int cnt=0;
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[i].size(); j++){
            for(int k=0; k<map[i][j].size(); k++){
                if(map[i][j][k]==1){
                    cnt++;
                }
            }
        }
    }
    return cnt; 
}

void makestep(std::tuple<int,int,int>& curr, const std::pair<char, int>& pattern, std::vector<std::vector<std::vector<int>>>& map){
    for(int i=0; i<pattern.second; i++){
        switch (pattern.first){
            case 'U': std::get<0>(curr)+=1;
            break;
            case 'D': std::get<0>(curr)-=1;
            break;
            case 'R': std::get<1>(curr)+=1;
            break;
            case 'L': std::get<1>(curr)-=1;
            break;
            case 'F': std::get<2>(curr)+=1;
            break;
            case 'B': std::get<2>(curr)-=1;
            break;
        }
        map[std::get<0>(curr)][std::get<1>(curr)][std::get<2>(curr)] =1;   
    }
}

