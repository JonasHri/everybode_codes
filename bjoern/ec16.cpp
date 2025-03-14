#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>

int countSymbol(const std::string& currWheel);
std::string calcWheel(const std::vector<std::vector<std::string>>& wheels, const std::vector<int>& turns, std::vector<int>& currPos);
void resizeVector(std::vector<std::string>& v);

int main(){
    std::vector<int> turns; 
    std::vector<std::vector<std::string>> wheels;

    std::string line;
    std::fstream file("everybody_codes_e2024_q16_p1.txt");
    std::getline(file, line);
    std::stringstream ss;
    ss << line;
    int a; 
    while(ss>>a){
        turns.push_back(a);
        if(ss.peek()==','){
            ss.ignore(); 
        }
    }
    wheels.reserve(turns.size()); 
    
    while(std::getline(file, line)){
        ss <<line; 
        std::string cat;
        int count=0; 
        for(int i=0; i<line.length(); i+=4){
            cat=line.substr(i, 3);
            // std::cerr << cat << std::endl; 
            wheels[count].push_back(cat);
            count++; 
        }
    }

    // std::cout<< wheels[1][2]<<std::endl; 
    // std::cout << countSymbol(" -_- -.- ^_^") <<std::endl; 
    std::string currWheel; 
    std::vector<int> currPos;
    for(int i=0; i< turns.size(); i++){
        currPos.push_back(0); 
        resizeVector(wheels[i]); 
    }
    // std::cout << "currpos size: "<<currPos.size() << " turns size: "<<turns.size() <<std::endl; 
    for(int i=0; i<100; i++){
        currWheel= calcWheel(wheels, turns, currPos);
    }
    std::cout << currWheel <<std::endl; 
    std::cout << countSymbol(currWheel) <<std::endl; 

    return 0; 
}

void resizeVector(std::vector<std::string>& v){
    int numEmptyStrings=0; 
    for(int i=0; i<v.size(); i++){
        if(v[i]!="   "){
            numEmptyStrings++;
            // std::cout << v[i] << std::endl; 
        }
        else{
            break;
        }
    }
    // std::cout << numEmptyStrings <<std::endl; 
    v.resize(numEmptyStrings); 
}

std::string calcWheel(const std::vector<std::vector<std::string>>& wheels, const std::vector<int>& turns, std::vector<int>& currPos){
    std::string erg;
    for(int i=0; i< currPos.size(); i++){
        currPos[i]+= turns[i];
        currPos[i] %= wheels[i].size();
        std::string tmp = wheels[i][currPos[i]]; 
        // std::cout << tmp <<std::endl; 
        erg += tmp;
        erg += " ";  
        // std::cout << currPos[i] << " @ "<< i<<" size: " << wheels[i].size() << std::endl; 
    }
    return erg; 
    
}

int countSymbol(const std::string& currWheel){
    int erg=0;
    std::unordered_set<char> searched;
    for(const char& c: currWheel){
        if(c==' '){
            continue;
        }
        if(searched.contains(c)){
            continue;
        }
        auto count= std::ranges::count(currWheel, c);
        // std::cout << "char: "<<c <<" count: "<< count<<std::endl; 
        if(count>=3){
            erg++;
            count-=3;
            while(count>0){
                erg++;
                count--;
            }
        }
        searched.insert(c); 
    }
    return erg; 
}