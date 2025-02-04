#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

int buildPyramid(int numBlocks, int priests, int acolytes);

int main(){
    int numPriests;
    int numBlocks = 20240000; 
    int acolytes = 1111; 

    std::string line;
     std::fstream file("everybody_codes_e2024_q08_p2.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    std::getline(file, line);
    numPriests= std::stoi(line);

    int erg= buildPyramid(numBlocks, numPriests, acolytes);
    std::cout << erg << std::endl; 

    // int test= buildPyramid(50, 3, 5);
    // std::cout << test << std::endl; 
    return 0; 
}

int buildPyramid(int numBlocks, int priests, int acolytes){
    int width=1;
    int thickness=1;
    numBlocks--;
    while(numBlocks> 0){
        // std::cout << "Blocks remaining: "<< numBlocks << " width: " << width << " thickness: " << thickness <<std::endl;  
        // std::cout << "blocks consumed: "<<width << "*"<<thickness<<"="<< width * thickness << std::endl; 
        width+=2; 
        thickness = (thickness*priests)%acolytes;
        numBlocks -= width * thickness; 
    }
    return width * (-numBlocks);
}