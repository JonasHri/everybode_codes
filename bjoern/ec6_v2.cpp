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
        //müssend ei Stirngs noch umdrehen:
        auto tmp=*erg; 
        std::reverse(tmp.begin(), tmp.end());
        for(const std::string p: tmp){
            std::cout <<p;
        }
        std::cout <<"@"<<std::endl; 
        // c:\Users\Björn Staats\Downloads\everybody_codes_e2024_q07_p2.txt
    } else{
        std::cout << "no erg" <<std::endl;
    }

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
    /*
    std::cout << "lens size: "<<  lens.size() << std::endl;

    std::vector<int> quantities;
    quantities.reserve(maxValue+1);

    std::cout << "max value: "<< maxValue << " at: " << *resIt << std::endl; 
    //std::cout << "it first: "<<*lens.begin() << " it-last: "<<*lens.end()<<std::endl; 

     
    std::cout << "iterator test"<< std::endl; 
    std::vector<int>::iterator it= lens.end();
    it++; 
    std::cout << *(it) << std::endl; 
    std::cout << lens.size() << std::endl; 
    for(std::vector<int>::iterator it= lens.begin(); it!= lens.end(); it++){
        std::cout << *it << std::endl;
        std::cout<< "naseweise"<< std::endl;  
    }
    for(int i=0; i< lens.size(); i++){
        std::cout << lens[i] <<std::endl; 
    }
    std::cout << "iterator test ende"<< std::endl; 
    

    for(int i=0; i<=maxValue; i++){
        for(const int l: lens){
            if(l==i){
                quantities[i]++;
            }
        }
    }
    for(int i=0; i<=maxValue; i++){
        std::cout << i << ": "<< quantities[i]<<std::endl;
    }
    int uniqLen;
    for(int i=0; i<=maxValue; i++){
        if(quantities[i]==1){
            std::cout <<"found 1: "<< i <<std::endl;
            uniqLen=i;
        }
    }
    for(int i=0; i<paths.size(); i++){
        if (lens[i]==uniqLen){
            return paths[i];
        }
    }
    return std::nullopt; 
    */
