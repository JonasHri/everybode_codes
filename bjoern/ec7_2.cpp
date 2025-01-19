#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>


int main(){
    std::vector<std::pair<std::string, std::string>> rules;
    std::vector<std::string> map;

    std::string line;
    std::fstream file("everybody_codes_e2024_q07_p2.txt");
    if(!file.is_open()){
        std::cerr<< "file not found \n";
        return 1; 
    }
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ':');
        //std::cout << "name: " <<name << std::endl; 
        std::string rule; 
        std::string token;
        size_t pos=-1;
        while(ss>>token) {
            while ((pos=token.rfind(',')) != std::string::npos) {
                token.erase(pos, 1);
            }
            rule = token;   
        }
        rules.push_back(std::make_pair(name, rule));
        //std::cout << rule <<std::endl; 
    }

    //parse map:
    std::string map;
    std::stack<std::string> stack;
    std::fstream file2("everybody_codes_e2024_q07_p2_MAP.txt");
    if(!file2.is_open()){
        std::cerr<< "file not found \n";
        return 1; 
    }
    while(std::getline(file2, line)){
        std::stringstream ss(line);
        
    }


}