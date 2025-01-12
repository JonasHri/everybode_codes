#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <array>
#include <optional>

std::optional<std::vector<std::string>> findUniq(const std::vector<std::vector<std::string>> paths);

int main(){
    std::unordered_map<std::string, std::string> input;

    std::string line;
    std::fstream file("everybody_codes_e2024_q06_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not foiund"<<std::endl;
    }
    while(std::getline(file, line)){
        size_t sep= line.find(':');
        std::string father = line.substr(0, sep);
        std::string kids = line.substr(sep+1);
        input.insert({father, kids});
    }

    /*
    for(const std::pair<const std::string, std::vector<std::string>>& p: input){
        std::cout <<p.first <<": ";
        for(const auto& s: p.second){
            std::cout << s<< " ";
        } 
        std::cout << std::endl; 
    }
    */
    std::vector<std::string> path; 
    std::vector<std::vector<std::string>> paths; 
    std::pair<std::string, std::string> curr; 
    for(const std::pair<const std::string, std::string>& node: input){
        if(node.second.contains('@')){  //gibts in c++23 :)
            path.clear();
            path.push_back(node.first);
            curr= node; 
            while(curr.first!="RR"){
                for(const std::pair<const std::string, std::string>& otherNode: input){
                    if(otherNode.second.contains(curr.first)){
                        curr=otherNode; 
                        path.push_back(curr.first);
                    }
                }
            }
            paths.push_back(path);
        }
    }
    if(auto erg=findUniq(paths)){
        std::cout << "ergebnis ist: ";
        for(int i= erg->size() -1; i>=0; i--){
            //std::cerr << i; 
          //  std::cout <<i << ": "; 
            std::cout << (*erg)[i]<< " ";
        }
        //std::cout << (*erg)[0];
        /*std::cout << "\n und das 2." << std::endl;
        for(const auto l: *erg){
            std::cout << l<<" ";
        } */
        std::cout <<std::endl; 
    } else{
        std::cout << "no erg" <<std::endl;
    }

    return 0; 
}

std::optional<std::vector<std::string>> findUniq(const std::vector<std::vector<std::string>> paths){
    int heightA=0;
    int heightB=0; 
    int currPos=0;
    for(std::vector<std::string> p:paths){
        int tmp= p.size();
        if(heightA==0){
            heightA=tmp;
        }else if(heightB==0){
            heightB=tmp;
        } else{
            if(tmp==heightA && heightA==heightB){
                continue; 
            } else if(tmp==heightA && heightA!=heightB){
                return paths[1];
            } else if(tmp==heightB && heightA != heightB){
                return paths[0];
            } else if(heightA == heightB && tmp!=heightA){
                return paths[currPos];
            }
        }
        currPos++; 
    }
    return std::nullopt; 
}