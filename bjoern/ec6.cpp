#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

struct Node{
    std::string name;
    std::list<Node> children; 
    

    Node(std::string n): name(n) 
    {
    }
};


int main(){

    std::unordered_map<std::string, std::string> input; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q06_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not foiund"<<std::endl;
    }
    while(std::getline(file, line)){
        if(size_t sepCol = line.find(':')!= std::string::npos){
            std::string father= line.substr(0, sepCol);
            Node fatherNode(father);
            std::string tmp= line.substr(sepCol+1);
            while(size_t sepKom = tmp.find(',') != std::string::npos){
                
            }
        }
        else{
            std::cerr<< "couldn´t parse line"<< line <<std::endl; 
        }
        
    }





    return 0; 
}