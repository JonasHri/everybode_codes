#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <optional>
#include <algorithm>
#include <unordered_set>

namespace std{
    ostream& operator<<(ostream& os, const vector<string>& vs){
        for(const auto& s: vs){
            os<<s <<endl;
        }
        os<<endl; 
        return os; 
    }
}

int moveThroughTrack(const std::vector<std::string>& map, const std::string& rules);
void energy(const std::vector<std::string>& map, const std::string& rules, int& currEnergie, int& energieCnt, int x, int y, int pos);
std::optional<std::pair<int,int>> makeNextStep(const std::vector<std::string>& map, std::vector<std::string>& visited, int x, int y);
int tryPaths(const std::vector<std::string>& map, const std::string& opponent); 

int main(){
    std::vector<std::string> map;
    std::string opponent; 

    std::string line; 
    {
        std::fstream file("ec7p3map.txt");
        while(std::getline(file, line)){
            map.push_back(line);
        }
        file.close();
    } 
    {
        std::fstream file("everybody_codes_e2024_q07_p3.txt");
        std::getline(file, line);
        size_t sep= line.find(':');
        line= line.substr(sep+1);
        while((sep=line.find(','))!=std::string::npos){
            opponent.append(line.substr(0, sep));
            line=line.substr(sep+1);
        }
        opponent.append(line); 
    }
 
    int numWins= tryPaths(map, opponent);
    std::cout << numWins <<std::endl; 
    return 0;
}

int tryPaths(const std::vector<std::string>& map, const std::string& opponent){
    int opponentScore = moveThroughTrack(map, opponent);
    int numWins=0; 
    std::string plan ="+++++---===";
    std::unordered_set<std::string> tried; 
    std::sort(plan.begin(), plan.end());
    while(std::next_permutation(plan.begin(), plan.end())){
        if(tried.contains(plan)){
            continue; 
        }
        tried.insert(plan);
        std::cout << "trying: "<< plan <<std::endl; 
        if(moveThroughTrack(map, plan) > opponentScore){
            numWins ++; 
        }
    }
    return numWins; 
}

int moveThroughTrack(const std::vector<std::string>& map, const std::string& rules){
    int currX=0, currY=0; 
    int numRounds=0, rulesPos=0;  
    int currEnergy=10; 
    int energieCnt=0; 
    std::vector<std::string> visited= map; 
    //std::cout << "started moving "<< std::endl; 
    while(numRounds < 2024){
        if(auto step= makeNextStep(map, visited, currX, currY )){
            currX= (*step).first;
            currY= (*step).second; 
        } else{
            std::cout << map[currX][currY]<<std::endl; 
            std::cout << map[currX][currY-1]<< ", " << std::endl; 
            std::cout << "returned nullopt at: "<< currX <<", " <<currY << " von: "<< map[0].length() <<std::endl; 
            // std::cout << map[cur][] <<std::endl; 
            std::cout << map <<std::endl; 
            std::cout <<visited<< std::endl; 
            return energieCnt; 
        }
        if(map[currX][currY]=='S'){
            visited = map; 
            numRounds++;
        }
        energy(map, rules, currEnergy, energieCnt, currX, currY, rulesPos);
        rulesPos = (rulesPos +1) % rules.size(); 
    }
    return energieCnt; 
}


void energy(const std::vector<std::string>& map, const std::string& rules, int& currEnergie, int& energieCnt, int x, int y, int pos){
    if(map[x][y]=='+'){
        currEnergie++;
    } else if(map[x][y]=='-'){
        currEnergie--;
    } else{
        if(rules[pos]=='-'){
            currEnergie--;
        } else if(rules[pos]=='+'){
            currEnergie++;
        }
    }
    energieCnt += currEnergie; 
}


std::optional<std::pair<int,int>> makeNextStep(const std::vector<std::string>& map, std::vector<std::string>& visited, int x, int y){
    // std::cout << x << ", "<< y <<std::endl; 
    if(x==0 && y==0){
        visited[0][1]=='#'; 
        return (std::make_pair(0, 1));
    }
    std::vector<std::pair<int,int>> dirs={
        {1,0}, {0,1}, {-1,0}, {0,-1}
    }; 
    for(const auto [dx, dy]: dirs){
        int newX= x+dx;
        int newY= y+dy;
        if(newX<0 || newY<0 || newX >= map.size() || newY >= map[0].length()){
            continue;
        }
        if(visited[newX][newY]=='#'){
            continue; 
        }
        if(map[newX][newY]=='+' || map[newX][newY]=='-' || map[newX][newY]=='=' || map[newX][newY]=='S'){
            visited[newX][newY]='#';
            return std::make_pair(newX, newY);
        }
    }
    return std::nullopt; 
}