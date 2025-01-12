#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <array>


int main(){
    std::unordered_map<std::string, std::vector<std::string>> input;

    std::string line;
    std::fstream file("everybody_codes_e2024_q06_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not foiund"<<std::endl;
    }
    while(std::getline(file, line)){
        size_t sep= line.find(':');
        std::string father = line.substr(0, sep);
        std::vector<std::string> children;
        std::string kids = line.substr(sep+1);
        std::string kid; 
        sep= kids.find(',');
        while(sep!=std::string::npos){
            //std::cout << kids << sep <<  std::endl;  
            kid= kids.substr(0, sep);
            kids= kids.substr(sep+1);
            sep= kids.find(',');
            children.push_back(kid);
        }
        children.push_back(kids); 
        input.insert({father, children});
    }

    for(const std::pair<const std::string, std::vector<std::string>>& p: input){
        std::cout <<p.first <<": ";
        for(const auto& s: p.second){
            std::cout << s<< " ";
        } 
        std::cout << std::endl; 
    }

    



    return 0; 
}