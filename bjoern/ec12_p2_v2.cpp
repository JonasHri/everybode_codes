#include <iostream>
#include <string>
#include <fstream>  
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <chrono>
#include <optional>


struct pairHash{
    template<typename T, typename U>
    std::size_t operator() (const std::pair<T,U>& p) const{
        return std::hash<T>() (p.first) ^ std::hash<U>()(p.second);
    }
};
char& at(std::vector<std::string>& map, const std::pair<int,int>& pos){
    return map[pos.first][pos.second];
}
const char& at(const std::vector<std::string>& map, const std::pair<int,int>& pos){
    return map[pos.first][pos.second];
}
std::pair<int,int> operator+(const std::pair<int,int>& a, const std::pair<int,int>& b){
    return {a.first+b.first, a.second+b.second}; 
}

std::optional<std::vector<std::pair<std::pair<int, int>, int>>> bfs(const std::vector<std::string>& map, const char& target, const int& numTargets, std::pair<int,int>& pos);

int main(){
    std::vector<std::string> map;

    std::ifstream file("everybody_codes_e2024_q15_p2.txt");
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
 
    // Ein kleinbuchstaben als Startpunktmarker:
    map[0][startcol]='a';

    // Die Buchstaben / Ziele auf der Karte bestimmen, ebenso ihre Anzahl
    std::unordered_map<char, int> targets;
    for(const std::string& row: map){
        for(const char& c: row){
            if(c=='#' || c=='~' || c=='.'){
                continue;
            }
            targets[c]++;
        }
    }
    
    // Jeden key extrahieren, um jede Permuation durchgehen zu können:
    std::vector<char> keys;
    for(const auto target: targets){
        keys.push_back(target.first);
    }

    
    // Eine Liste aller Koordinaten für jeden Buchstaben
    std::unordered_map<char, std::vector<std::pair<int,int>>>startPositions; 
    for(const char& startpoint: keys){
        if(auto allTargetPositions= bfs(map, startpoint, targets[startpoint], {0, startcol})){
            auto allTargetPositios_dereferenced= *allTargetPositions;
            std::vector<std::pair<int,int>> targetPositions;
            for(const auto& targetPosition: allTargetPositios_dereferenced){
                targetPositions.push_back(targetPosition.first); 
            }
            startPositions.insert({startpoint, targetPositions});
        }
    }
    
    // Die Pfade zwischen jeden Startpunkt und Endpunkt berechnen
    std::unordered_map<std::pair<char, char>, int> calcedPaths;
    for(const char& startpoint: keys){
        std::vector<std::pair<int,int>> startpoints = startPositions[startpoint]; 
        for(std::pair<int,int> sp: startpoints){
            for(const char& endpoint: keys){
                if(auto dists= bfs(map, endpoint, targets[endpoint], sp)){
                    auto d= *dists; 
                    for(const auto& d_dist: d){
                        calcedPaths.insert({{startpoint, endpoint}, d_dist.second});
                    }
                }
            }
        }
    }

    // Kürzeste Distanz finden, die jeden Punkt besucht:
    

    return 0;
}

std::optional<std::vector<std::pair<std::pair<int, int>, int>>> bfs(const std::vector<std::string>& map, const char& target, const int& numTargets, std::pair<int,int>& pos){
    std::vector<std::pair<std::pair<int, int>, int>> result;
    std::queue<std::pair<std::pair<int,int>, int>> q;
    q.push({pos, 0});

    std::unordered_set<std::pair<int,int>, pairHash> visited;
    int numFound=0; 
    std::vector<std::pair<int,int>> dirs {{1,0}, {-1,0}, {0,1}, {0,-1}};

    while(!q.empty()){
        std::pair<std::pair<int, int>, int> curr= q.front();
        std::pair<int,int> currPos = curr.first;
        int currDist= curr.second;
        q.pop();
        visited.insert(currPos); 

        // Ein Target gefunden:
        if(at(map, currPos)== target){
            result.push_back(curr);
            numFound++;
            // so viele Targets gefunden, wie da sein sollen:
            if(numFound== numTargets){
                return result; 
            }
        }

        for(const auto& dir: dirs){
            std::pair<int,int> nextPos = currPos + dir;
            if(nextPos.first <0 ){
                continue;
            }
            if(visited.contains(nextPos)){
                continue;
            }
            char nextSym= at(map, nextPos);
            if(nextSym=='#' || nextSym =='~'){
                continue;
            }
            q.push({nextPos, currDist +1});
        }
    }
    return std::nullopt; 
}