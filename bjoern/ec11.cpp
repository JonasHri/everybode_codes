#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <limits>

namespace std{
    ostream& operator<< (ostream& os, const vector<string>& vs){
        for(string s: vs){
            os<<s<<", ";
        }
        return os;
    }
}; 

int calcNumTermites(std::unordered_map<std::string,std::vector<std::string>>& conversions, const std::string& startTermite);

int main(){
    std::unordered_map<std::string,std::vector<std::string>> conversions;

    std::string line;
     std::fstream file("everybody_codes_e2024_q11_p3.txt");
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

    int biggest=-1;
    int smallest= std::numeric_limits<int>::max(); 
    for(const auto& starttermite: conversions){
        std::cout << "starting with: "<< starttermite.first <<std::endl; 
        int num= calcNumTermites(conversions, starttermite.first);
        if(num<smallest){
            smallest=num;
        }
        if(num>biggest){
            biggest=num;
        }
    }

    int diff= biggest-smallest;
    std::cout << diff << std::endl;

    return 0; 
}


int calcNumTermites(std::unordered_map<std::string,std::vector<std::string>>& conversions, const std::string& startTermite){
    std::vector<std::string> currentTermites; 
    currentTermites.push_back(startTermite);
    for(int i=0; i<20; i++){
        std::vector<std::string> nextGen; 
        for(const std::string& s: currentTermites){
            for(std::string termiteToAdd: conversions[s]){
                nextGen.push_back(termiteToAdd);
            }
        }
        currentTermites=nextGen; 
    }
    return currentTermites.size(); 
}