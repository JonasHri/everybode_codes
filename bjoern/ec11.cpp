#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

namespace std{
    ostream& operator<< (ostream& os, const vector<string>& vs){
        for(string s: vs){
            os<<s<<", ";
        }
        return os;
    }
}

int main(){
    std::unordered_map<std::string,std::vector<std::string>> conversions;

    std::string line;
     std::fstream file("everybody_codes_e2024_q11_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        size_t delimiter= line.find(':');
        std::string origin = line.substr(0, delimiter); 
        line= line.substr(delimiter+1); 
        std::stringstream ss;
        ss <<line;
        std::vector<std::string> dest;
        for(std::string destination; std::getline(ss, destination, ',');){
            dest.push_back(destination);
        }
        conversions.insert({origin, dest});
    }

    std::string startTermite="A";
    std::vector<std::string> currentTermites; 
    currentTermites.push_back(startTermite);
    for(int i=0; i<4; i++){
        std::vector<std::string> nextGen; 
        for(const std::string s: currentTermites){
            for(std::string termiteToAdd: conversions[s]){
                nextGen.push_back(termiteToAdd);
            }
        }
        currentTermites=nextGen; 
    }

    std::cout<< currentTermites.size() <<std::endl; 
    
}