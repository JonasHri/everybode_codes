#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <tuple>

void makestep(std::tuple<int,int,int>& curr, const std::pair<char, int>& pattern, std::vector<std::vector<std::vector<int>>>& map);
int calcsize(const std::vector<std::vector<std::vector<int>>>& map);

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
}

int main(){ 
    std::vector<std::vector<std::pair<char, int>>> growthPattern;
    std::ifstream file("everybody_codes_e2024_q14_p2.txt");
    if (!file) {
        std::cerr << "File not found: " << "everybody_codes_e2024_q14_p2.txt" << std::endl;
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

    std::tuple<int,int,int> pos(200,200,200); 
    // int treesize=0;
    int cnt =1, rowcnt=1; 
    for(auto row: growthPattern){
        std::cout << "on row: "<< rowcnt <<"/"<<growthPattern.size() <<std::endl;
        for(auto pattern: row){
            std::cout << cnt <<"/"<< row.size()<<" size: " <<pattern.second <<  std::endl; 
            cnt ++; 
            makestep(pos, pattern, map);
        }    
        int erg= calcsize(map);
        std::cout <<erg<<std::endl; ; 
        cnt=1;
        pos={200,200,200}; 
        rowcnt++; 
    }
    std::cout << "ende "<<std::endl; 
    return 0; 
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

