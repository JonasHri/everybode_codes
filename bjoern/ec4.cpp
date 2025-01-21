#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::vector<int> nails;

    std::string line;
    std::fstream file("everybody_codes_e2024_q04_p1.txt");
    if(!file.is_open()){
        std::cerr << "file not found \n";
        return 1;
    }
    while(std::getline(file, line)){
        nails.push_back(std::stoi(line));
    }

    int minValue=100000, minIndex;
    for(int i=0; i<nails.size(); i++){
        if(nails[i]<minValue){
            minValue= nails[i];
            minIndex=i; 
        }
    }

    int hits=0; 
    for(int nail: nails){
        while(nail>minValue){
            hits++;
            nail--;
        }
    }
    std::cout << hits <<std::endl;
    return 0; 
}