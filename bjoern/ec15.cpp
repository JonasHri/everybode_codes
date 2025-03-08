#include <iostream>
#include <string>
#include <fstream>  
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>

struct pairHash{
    std::size_t operator() (const std::pair<int,int>& p)const{
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second); 
    }
};
std::ostream& operator<<(std::ostream& os, const std::pair<int,int>& a){
    os << a.first << ", "<< a.second;
    return os; 
}
std::pair<int,int> operator+(const std::pair<int,int>& a, const std::pair<int,int>& b){
    return {a.first+b.first, a.second+b.second};
}
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vs){
    for(const std::string s: vs){
        os<<s <<std::endl; 
    }
    return os; 
}

std::pair<std::pair<int,int>,int> bfs(const std::vector<std::string>& map, std::vector<char>& goal, const int& startrow, const int& startcol );
std::pair<std::pair<int,int>,int> bfs2(const std::vector<std::string>& map, const char& goal, const int& startrow, const int& startcol );

int main(){
    std::vector<std::string> map;


    std::ifstream file("everybody_codes_e2024_q15_p2_TEST.txt");
    if (!file) {
        std::cerr << "File not found" << std::endl;
        return -1;
    }
    std::string line; 
    while(std::getline(file, line)){
        map.push_back(line);
    }

    int startcol=0;
    // find start -> its in the top row 
    for(int i=0; i<map[0].length(); i++){
        if(map[0][i]=='.'){
            startcol=i;
            break;
        }
    }
    
    // Alle uniquen Pflanzen zählen:
    std::vector<char> toFind;
    std::unordered_map<char, int> occurances; 

    for (const std::string& line : map) {
        for (const char& c : line) {
            if (c == '#' || c == '~' || c == '.') {
                continue;  
            }
            bool found = false;
            for (int i = 0; i < toFind.size(); i++) {
                if (toFind[i] == c) {  
                    found = true;  
                }
            }
            occurances[c]+=1 ; 
            if (!found) {  
                toFind.push_back(c);  
            }
        }
    } 
    std::sort(toFind.begin(), toFind.end());
    
    int res=std::numeric_limits<int>::max(); 
    // startpos markieren, damit diese wiedergefunden werden kann 
    map[0][startcol]= 'a';
    while (std::next_permutation(toFind.begin(), toFind.end())){
        toFind.push_back('a');
        // for(const char c: toFind){
        //     std::cout << c <<" ";
        // }
        // std::cout << std::endl;
        std::vector<std::pair<int,int>> pos={{0, startcol}};
        int erg=0;
        for(const char& target: toFind){
            for(const auto& occ: pos){
                std::vector<std::pair<std::pair<int,int>,int>> next = bfs2(map, target, occurances[target], occ.first, occ.second);
                erg += next.second;
                pos.clear();
                for(const auto& n: next){
                    pos.push_back(n.first);
                } 
            }
        }
        // while(!goal.empty()){
        //     // std::cerr <<"hier startpos: "<< pos <<std::endl;
        //     if(pos.first<0 || pos.second<0){
        //         break; 
        //     }
        //     std::pair<std::pair<int,int>,int> next = bfs(map, goal, pos.first, pos.second);
        //     erg += next.second;
        //     pos= next.first; 
        //     break; 
        // }
        // std::cout << erg <<std::endl; 
        // Jetzt noch den start wiederfinden...
        // goal.push_back('a');
        // erg += bfs(map, goal, pos.first, pos.second).second;
        if(erg < res ){
            res= erg; 
        }
        break; 
    }
    

    std::cout << res <<std::endl;


    return 0; 
}

std::vector<std::pair<std::pair<int,int>,int>> bfs2(const std::vector<std::string>& map, const char& goal, const int& occurances, const int& startrow, const int& startcol ){
    std::queue<std::pair<std::pair<int,int>,int>> q;
    q.push({{startrow, startcol}, 0});

    std::unordered_set<std::pair<int,int>, pairHash> visited;
    std::vector<std::pair<int,int>> dirs {{1,0}, {-1,0}, {0,1}, {0,-1}};

    std::vector<std::string> control = map; 

    while(!q.empty()){
        auto curr= q.front();
        q.pop(); 
        std::pair<int,int> currPos= curr.first; 
        control[currPos.first][currPos.second]='k';
        // std::cout << currPos << ": "<<map[currPos.first][currPos.second]<< std::endl; 
        int dist= curr.second;
        visited.insert(currPos); 
        // std::cout << "currpos:"<<currPos<<std::endl; 
        if (map[currPos.first][currPos.second] == goal) {
            std::cout << "found " << map[currPos.first][currPos.second] << " with " << dist << " @: "<< currPos.first <<", "<<currPos.second<<std::endl; 
            control[currPos.first][currPos.second]='O'; 
            std::cout << control <<std::endl; 
            return curr; 
        }
        for(auto dir: dirs){
            std::pair<int,int> nextPos= currPos + dir; 
            if(nextPos.first<0 || nextPos.second <0 || nextPos.first >= map.size() || nextPos.second>=map[0].length()){
                continue;
            }
            if(visited.contains(nextPos)){
                continue;
            }
            if(map[nextPos.first][nextPos.second]=='#' || map[nextPos.first][nextPos.second]=='~'){
                continue;
            }
            q.push({nextPos, dist+1});
        }
    }
    return {{-1,-1},-1};
}

std::pair<std::pair<int,int>,int> bfs(const std::vector<std::string>& map,std::vector<char>& goal, const int& startrow, const int& startcol ){
    std::queue<std::pair<std::pair<int,int>,int>> q;
    q.push({{startrow, startcol}, 0});

    std::unordered_set<std::pair<int,int>, pairHash> visited;
    std::vector<std::pair<int,int>> dirs {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int pointer=0; 
    while(!q.empty()){
        auto curr= q.front();
        q.pop(); 
        std::pair<int,int> currPos= curr.first; 
        if(map[currPos.first][currPos.second]!='.'){
        }
        std::cout << currPos << ": "<<map[currPos.first][currPos.second]<< std::endl; 
        int dist= curr.second;
        visited.insert(currPos); 
        // std::cout << "currpos:"<<currPos<<std::endl; 
        if (map[currPos.first][currPos.second] == goal.front()) {
            std::cout << "found " << map[currPos.first][currPos.second] << " with " << dist << std::endl;
            goal.erase(goal.begin());  
            return curr; 
        }
        for(auto dir: dirs){
            std::pair<int,int> nextPos= currPos + dir; 
            if(nextPos.first<0 || nextPos.second <0 || nextPos.first >= map.size() || nextPos.second>=map[0].length()){
                continue;
            }
            if(visited.contains(nextPos)){
                continue;
            }
            if(map[nextPos.first][nextPos.second]=='#' || map[nextPos.first][nextPos.second]=='~'){
                continue;
            }
            q.push({nextPos, dist+1});
        }
    }
    return {{-1,-1},-1}; 
}