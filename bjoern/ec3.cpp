#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool increase(std::vector<std::vector<int>>& map);
int count(const std::vector<std::vector<int>>& map);
std::vector<std::vector<int>> makeintmap (const std::vector<std::string>& map);

int main(){
    std::vector<std::string> map; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q03_p3.txt");
    if(!file.is_open()){
        std::cerr << "file not foiund \n";
        return 1;
    }

    while(std::getline(file, line)){
        map.push_back(line);
    }

    std::vector<std::vector<int>> numMap = makeintmap(map);
    while(increase(numMap)){

    }
    /*
    for(const std::string m: map){
        std::cout << m << std::endl; 
    }
    */
    int erg= count(numMap);
    std::cout << erg << std::endl; 
    return 0; 
}

int count(const std::vector<std::vector<int>>& map){
    int result=0; 
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<  map[i].size(); j++){
            if(map[i][j]==-1){
                continue; 
            }
            char curr= map[i][j];
            int num = curr ;
            result += num; 
        }
    }
    return result; 
}

std::vector<std::vector<int>> makeintmap (const std::vector<std::string>& map){
    std::vector<std::vector<int>> res; 
    std::vector<int> line;
    for(const std::string l: map){
        line.clear();
        for(const char c: l){
            if(c=='.'){
                line.push_back(-1);
            }else if(c=='#'){
                line.push_back(0);
            }
            else{
                std::cerr<< "illegal char met: "<< c <<std::endl; 
            }
        }
        res.push_back(line);
    }
    return res; 
}


bool increase(std::vector<std::vector<int>>& map){
    bool changed=false; 
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<  map[i].size(); j++){
            if(map[i][j]==-1){
                continue; 
            }
            if(map[i][j]==0){
                changed= true;
                map[i][j]=1; 
            }
            //alle 4 nachbarn sind gleich:
            std::vector<std::pair<int, int>> directions ={
                {-1,0}, {1,0}, {0,-1}, {0,1} , {1,1}, {1,-1}, {-1, 1}, {-1,-1}
            };
            bool allEqual=true;
            for( auto[dx, dy]: directions){
                int xnew = i+dx; 
                int ynew = j+dy;
                if(xnew<0 || ynew < 0 || xnew >= map.size() || map[i].size()){
                    allEqual=false; 
                    break; 
                }
                if(!(map[i][j]==map[xnew][ynew] || map[xnew][ynew] == map[i][j]+1)  ){
                    allEqual=false;
                    break;
                }
            }
            if(allEqual){
                changed= true;
                char curr = map[i][j];
                //std::cout << curr <<std:: endl; 
                int next= curr+1; 
                map[i][j]= next;   
                //std::cout << next << " h"<< std::endl; 
            }
        }
    }
    return changed; 
}
