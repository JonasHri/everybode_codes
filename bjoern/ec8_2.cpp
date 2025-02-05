#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

namespace std{
    ostream& operator<<(ostream& os, const std::vector<int>& v){
        for(const int& t: v){
            os << "["<<t<<"] "; 
        }
        return os; 
    }
}

int buildPyramid(int numBlocks, int priests, int acolytes);
int calcThickness(int thickness, int priests, int acolytes);
int removeBlocks(int width,const std::vector<int>& height, int priests, int acolytes);

int main(){
    int numPriests;
    int numBlocks = 202400000; 
    int acolytes = 10; 

    std::string line;
     std::fstream file("everybody_codes_e2024_q08_p3.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    std::getline(file, line);
    numPriests= std::stoi(line);

    int erg= buildPyramid(numBlocks, numPriests, acolytes);
    std::cout << erg << std::endl; 

    int test= buildPyramid(1964799, 2, 5);
    std::cout << test << std::endl; 
    return 0; 
}

int buildPyramid(int numBlocks, int priests, int acolytes){
    int width=1;
    int thickness=1;
    std::vector<int> rows; 
    rows.push_back(1);
    numBlocks--;
    while(numBlocks+removeBlocks(width, rows, priests, acolytes)> 0){
        // std::cout << rows << std::endl; 
        // std::cout << "Blocks remaining: "<< numBlocks << " width: " << width << " thickness: " << thickness <<std::endl;  
        // std::cout << "blocks consumed: "<<width << "*"<<thickness<<"="<< width * thickness << std::endl; 
        width+=2; 
        thickness = calcThickness(thickness, priests, acolytes);
        for(int& r: rows){
            r+= thickness;
        }
        rows.push_back(thickness);
        numBlocks -= width * thickness; 
    }
    // std::cout << rows << std::endl; 
    numBlocks += removeBlocks(width, rows, priests, acolytes); 
    return (-numBlocks);
}

int calcThickness(int thickness, int priests, int acolytes){
    // std::cout << "in calcthickmes"<< std::endl; 
    thickness = ((thickness * priests) %acolytes) +acolytes;
    return thickness; 
}

int removeBlocks(int width, const std::vector<int>& height, int priests, int acolytes){
    // std::cout << "in remove Blcoks "<<std::endl; 
    int erg=0; 
    for(int i=0; i<height.size()-1; i++){
        int tmp= (width * priests * height[i])%acolytes;
        erg+=  tmp; 
        if(i==0){
            continue;
        }
        erg+= tmp; 
    }
    return erg; 
}