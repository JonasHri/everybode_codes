#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


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


    return 0; 
}