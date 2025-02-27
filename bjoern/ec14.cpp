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

void markMap(std::vector<std::vector<std::vector<int>>>& uniqs, int x, int y, int z, char dir, int len);
int countMap(const std::vector<std::vector<std::vector<int>>>& uniqs);

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
    std::vector<std::vector<std::vector<int>>> uniqs(200, std::vector<std::vector<int>>(200, std::vector<int>(200, 0))); 



    for(auto day: grothPattern){
        // int x2=x, y2=y, z2=z;
        char dir= day.first;
        int len= day.second;
        switch (dir){
            case 'U': z+= len;
                if (z>maxheight){
                    maxheight=z;
                }
                markMap(uniqs, x, y, z, dir, len);
                break;
            case 'D': z-= len;
                markMap(uniqs, x, y, z, dir, len);
                break;
            case 'R': x+=len;
                markMap(uniqs, x, y, z, dir, len);
                break;
            case 'L': x-=len;
                markMap(uniqs, x, y, z, dir, len);
                break;
            case 'F': y+=len;
                markMap(uniqs, x, y, z, dir, len);
                break;
            case 'B': y-=len;
                markMap(uniqs, x, y, z, dir, len);
                break;
            default: std::cerr << "illegal instruction: "<<dir<<std::endl; 
        }
        // std::cout<<"gone: "<<dir<<" by: "<<len<< " height now: "<< z<<std::endl; 
        for(int i=0; i<len; i++){
            
        }
    }
    int erg= countMap(uniqs);
    std::cout << erg <<std::endl; 

    return 0; 
}

int countMap(const std::vector<std::vector<std::vector<int>>>& uniqs){
    int cnt=0;
    for(const auto& pl: uniqs){
        for(const auto& p: pl){
            for(const int& i: p){
                if(i==1){
                    cnt++;
                }
            }
        }
    }
    return cnt; 
}

void markMap(std::vector<std::vector<std::vector<int>>>& uniqs, int x, int y, int z, char dir, int len){
    for(int i=0; i<len; i++){
        switch (dir){
            case 'U': uniqs[x][y][z+i]=1;
                break;
                case 'D': uniqs[x][y][z-i]=1;
                break;
            case 'R': uniqs[x+i][y][z]=1;
                break;
            case 'L': uniqs[x-i][y][z]=1;
                break;
            case 'F': uniqs[x][y+i][z]=1;
                break;
            case 'B': uniqs[x][y-1][z]=1;
                break;
            default: std::cerr << "Fiif"<<dir<<std::endl; 
        }
    }
}