#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int calcPotion(const char& c);
std::vector<std::string> divideString(const std::string input, int len);

int main(){
    std::string enemies;
    std::string line; 
    //input part 1: 
    std::fstream file("everybody_codes_e2024_q01_p1.txt"); 
    if(!file.is_open()){
        std::cout << "Error: File not found" << std::endl;
        return 1;
    }
    while (std::getline(file, line)){
        enemies += line;
    }
    file.close(); 
    //input part 2:
    std::vector<std::string> enemies_round2;
    std::fstream file2("everybody_codes_e2024_q01_p2.txt");
    if(!file2.is_open()){
        std::cout << "Error: File2 not found" << std::endl;
        return 1;
    }
    while(std::getline(file2, line)){
        std::cout<< line << std::endl; 
        enemies_round2= divideString(line, 2); 
    }
    file2.close();
    //input part 3:
    std::vector<std::string> enemies_round3;
    std::fstream file3("everybody_codes_e2024_q01_p3.txt");
    if(!file3.is_open()){
        std::cout << "Error: File3 not found" << std::endl;
        return 1;
    }
    while(std::getline(file3, line)){
        std::cout<< line << std::endl; 
        enemies_round3= divideString(line, 3); 
    }
    file3.close();
    
    //output part 1:
    int erg=0;
    for(auto c: enemies){
        if(c=='A'){
            continue;
        } else if(c=='B'){
            erg++;
        } else if(c=='C'){
            erg +=3;
        }
        else{
            std::cout << "Error: " << c << std::endl;
        }
    }
    //std::cout << erg << std::endl;

    //output part 2:
    int erg2=0; 
    for(std::string pair: enemies_round2){
        int tmp; 
        int cnt=2; 
        if (pair[0]=='x'){
            tmp=calcPotion(pair[1]);
        } else if(pair[1]=='x'){
            tmp=calcPotion(pair[0]);
        } else{
            tmp= (calcPotion(pair[0])+ calcPotion(pair[1])+2); 
        }
        erg2 += tmp; 
        //std::cout << pair <<": "<< tmp << std::endl; 
    }
    std::cout <<"erg 2: " <<erg2 <<std::endl; 

    //output part 3
    int erg3=0; 
    for(std::string pair: enemies_round3){
        int tmp=0;
        int cnt=3;
        for(int i=0; i<3; i++){
            if(pair[i]=='x'){
                cnt--; 
            }
            tmp += calcPotion(pair[i]);
        }
        tmp += cnt * (cnt-1); 
        erg3 += tmp;
    }
    std::cout << erg3<<std::endl; 

}
std::vector<std::string> divideString(const std::string input, int len){
    std::vector<std::string> erg;
    erg.reserve(input.size()/len);
    for(int i=0; i<input.size(); i+=len){
        erg.push_back(input.substr(i, len));
    }
    return erg; 
}
int calcPotion(const char& c){
    switch (c){
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 3;
        case 'D': return 5;
        case 'x': return 0; 
        default: std::cout << c <<std::endl; 
        return -999999999;
    }
}