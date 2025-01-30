#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int numDots(int brigthnes);

int main(){
    std::vector<int> sparkballs;

    std::string line;
    std::fstream file("everybody_codes_e2024_q09_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        sparkballs.push_back(std::stoi(line));
    }

    std::vector<int> test={2,4,7,16};
    int erg=0;
    for(int ball: sparkballs){
        erg += numDots(ball);
    }
    std::cout << erg << std::endl; 

    return 0; 
}

int numDots(int brigthnes){
    if(brigthnes==1 || brigthnes==3 || brigthnes==5 || brigthnes==10){
        return 1;
    }
    
    if(brigthnes>10){
        brigthnes-=10;
    }else if(brigthnes>5){
        brigthnes -=5;
    }else if(brigthnes>3){
        brigthnes -=3;
    } else{
        brigthnes--;
    }
    return 1+ numDots(brigthnes);
}

