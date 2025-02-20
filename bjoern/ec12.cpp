#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <limits>
#include <optional>
#include <clocale>


int main(){
    std::vector<std::string> map; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q11_p3.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        map.push_back(line);
    }
    std::unordered_map<char, std::pair<int,int>> launchers= findLauchposition(map);


    while(true){
        if(auto pos= findTarget(map)){
            auto target = *pos;
            int dist = target.second - launchers['A'].second; 
        }
        else{
            break;
        }
    }

    return 0;
}
std::unordered_map<char, std::pair<int,int>> findLauchposition(const std::vector<std::string>& map){
    std::unordered_map<char, std::pair<int,int>> launchers; 
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[i].length(); j++){
            if(std::isupper(map[i][j])){
                if(map[i][j]=='T'){
                    continue;
                } else{
                    launchers.insert({map[i][j], std::make_pair(i,i)});
                }
            }
        }
    }
    return launchers; 
}

std::optional<std::pair<int,int>> findTarget(const std::vector<std::string>& map){
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[i].length(); j++){
            if(map[i][j]=='T'){
                return std::make_pair(i,j);
            }
        }
    }
    return std::nullopt; 
}