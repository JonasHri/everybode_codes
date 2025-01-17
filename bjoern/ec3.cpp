#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool increase(std::vector<std::string>& map);
int count(const std::vector<std::string>& map);

int main(){
    std::vector<std::string> map; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q03_p2.txt");
    if(!file.is_open()){
        std::cerr << "file not foiund \n";
        return 1;
    }

    while(std::getline(file, line)){
        map.push_back(line);
    }

    while(increase(map)){

    }
    
    for(const std::string m: map){
        std::cout << m << std::endl; 
    }

    int erg= count(map);
    std::cout << erg << std::endl; 
    return 0; 
}

int count(const std::vector<std::string>& map){
    int result=0; 
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<  map[i].length(); j++){
            if(map[i][j]=='.'){
                continue; 
            }
            char curr= map[i][j];
            int num = curr -'0';
            result += num; 
        }
    }
    return result; 
}




bool increase(std::vector<std::string>& map){
    bool changed=false; 
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<  map[i].length(); j++){
            if(map[i][j]=='.'){
                continue; 
            }
            if(map[i][j]=='#'){
                changed= true;
                map[i][j]='1'; 
            }
            //alle 4 nachbarn sind gleich:
            std::vector<std::pair<int, int>> directions ={
                {-1,0}, {1,0}, {0,-1}, {0,1}
            };
            bool allEqual=true;
            for( auto[dx, dy]: directions){
                int xnew = i+dx; //boarder checking ist egal. Der input ist nicht am rand :) :D
                int ynew = j+dy;
                if(!(map[i][j]==map[xnew][ynew] || map[xnew][ynew] == map[i][j]+1)  ){
                    allEqual=false;
                    break;
                }
            }
            if(allEqual){
                changed= true;
                char curr = map[i][j];
                std::cout << curr <<std:: endl; 
                int next= (curr-'0')+1; 
                map[i][j]= '0' + (char) next;   
                std::cout << next << " h"<< std::endl; 
            }
        }
    }
    return changed; 
}
