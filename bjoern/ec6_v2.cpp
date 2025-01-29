#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <array>
#include <optional>

std::optional<std::vector<std::string>> findUniq(const std::vector<std::vector<std::string>> paths);

namespace std{
    ostream& operator <<(ostream& os, const std::vector<std::string>& vl){
        std::vector<std::string>rev = vl;
        reverse(rev.begin(), rev.end());
        for(const std::string l: rev){
            os << l[0];
        }
        return os; 
    }
}

int main(){
    // std::unordered_map<std::string, std::string> input;
    
    std::vector<std::pair<std::string, std::string>> in; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q06_p3.txt");
    if(!file.is_open()){
        std::cerr <<"file not foiund"<<std::endl;
    }
    while(std::getline(file, line)){
        size_t sep= line.find(':');
        std::string father = line.substr(0, sep);
        std::string kids = line.substr(sep+1);
        // input.insert({father, kids});
        in.push_back(std::make_pair(father, kids));
    }
    std::cout <<"schiiissch"<<std::endl; 
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
    std::string curr; 
    for(const auto& [to, from]: in){
        if(from.contains("@")){  //gibts in c++23 :)
            // std::cout << "checking one "<<std::endl; 
            path.clear();
            path.push_back(to);
            curr= to; 
            while(curr!="RR"){
                for(const auto& [otherTo, otherFrom]: in){
                    if(otherFrom.contains(curr)){
                        // std::cout << "vorägnger gefunden"<<std::endl; 
                        curr=otherTo; 
                        path.push_back(curr);
                        break; 
                    }
                }
            }
            // std::cout << curr <<std::endl; 
            paths.push_back(path);
        }
    }

    
    if(auto erg=findUniq(paths)){
        std::cout << "ergebnis ist: ";
        //müssend ei Stirngs noch umdrehen:
        auto tmp=*erg; 
        std::reverse(tmp.begin(), tmp.end());
        for(const std::string p: tmp){
            //für p2 nur den ersten Buchstaben printen:
            std::cout <<p[0];
        }
        std::cout <<"@"<<std::endl;
    } else{
        std::cout << "no erg" <<std::endl;
    }

    std::cout<< paths[0]<<std::endl; 
    std::cout<< paths[10] <<std::endl; 
    return 0; 
}

std::optional<std::vector<std::string>> findUniq(const std::vector<std::vector<std::string>> paths){
    std::vector<int> lens;
    std::cout <<"es gibt paths: "<< paths.size()<< std::endl; 
    lens.reserve(paths.size());
    int maxValue= 0;
    for (int i=0; i<paths.size(); i++){
        lens[i]=paths[i].size();
        if(lens[i]>maxValue){
            maxValue=lens[i];
        }
    }
    std::cout << "lens size: "<<  lens.size() << std::endl;
    int* lenArr= new int[maxValue+1]; 
    for (int i=0; i<paths.size(); i++){
        lenArr[lens[i]]++;
       std::cout << i<< ": "<<lens[i]<< std::endl; 
    }
    int uniqLen=-1; 
    for(int i=0; i< maxValue+1; i++){
        if(lenArr[i] ==1){
            uniqLen=i; 
        }
    }
    delete[] lenArr;

    for(int i=0; i< paths.size(); i++){
        if(paths[i].size() == uniqLen){
            return paths[i];
        }
    } 

    return std::nullopt;
}
    