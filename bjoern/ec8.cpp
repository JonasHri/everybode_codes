#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int buildPyramid(int numblocks);

int main(){
    int numblocks;

    std::string line;
     std::fstream file("everybody_codes_e2024_q08_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    std::getline(file, line);
    numblocks= std::stoi(line);

    int erg= buildPyramid(numblocks); 
    std::cout << erg <<std::endl; 
    return 0;
}

int buildPyramid(int numblocks){
    int width=0;
    if(numblocks>=1){
        width=1;
        numblocks--;
    }
    int curr=1;
    while(numblocks>0){
        curr+=2;
        numblocks-=curr;
        width+=2;
    }
    std::cout <<"widht: "<< width<< std:: endl;
    std::cout << "Blöcke zu viel gebruacht: "<< numblocks <<std::endl; 
    int erg = width * (-numblocks); 
    return erg; 
}