#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <limits>
#include <optional>
#include <queue>
#include <clocale>
#include <algorithm>


int main(){
    std::vector<std::pair<char, int>> grothPattern; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q14_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        std::stringstream ss;
        ss << line; 
        std::string arg;
        while(std::getline(ss, arg, ',')){
            char c= arg.at(0);
            int i= std::stoi(arg.substr(1));
            grothPattern.push_back(std::make_pair(c, i));
        }
    }

    int x=0, y=0, z=0; //x: r-l, y= f-b, z= u-d
    int maxheight=0; 

    for(auto day: grothPattern){
        char dir= day.first;
        int len= day.second;
        switch (dir){
            case 'U': z+= len;
                if (z>maxheight){
                    maxheight=z;
                }
                break;
            case 'D': z-= len;
                break;
            case 'R': x+=len;
                break;
            case 'L': x-=len;
                break;
            case 'F': y+=len;
                break;
            case 'B': y-=len;
                break;
            default: std::cerr << "illegal instruction: "<<dir<<std::endl; 
        }
        // std::cout<<"gone: "<<dir<<" by: "<<len<< " height now: "<< z<<std::endl; 
    }
    std::cout << maxheight <<std::endl; 

    return 0; 
}

