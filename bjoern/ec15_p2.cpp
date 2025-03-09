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

struct pairHash{
    template<typename T, typename U>
    std::size_t operator() (const std::pair<T,U>& p) const{
        return std::hash<T>() (p.first) ^ std::hash<U>()(p.second);
    }
};
struct nestedPairHash {
    std::size_t operator()(const std::pair<std::pair<int, int>, char>& p) const {
        std::size_t h1 = std::hash<int>()(p.first.first);
        std::size_t h2 = std::hash<int>()(p.first.second);
        std::size_t h3 = std::hash<char>()(p.second);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
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

std::vector<std::pair<std::pair<int,int>, int>> bfs(const std::vector<std::string>& map, const int& anzahl, const char& target, std::pair<int,int>& pos);

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
    
    // keys sortieren:
    std::sort(keys.begin(), keys.end());

    // startpunkt markieren mit kleinbuchstabe
    std::pair<int,int> pos {0, startcol};
    std::pair<int,int> startpos = pos;
    at(map, startpos)= 'a'; 

    std::vector<std::pair<std::pair<int,int>,int>> dist {{startpos, 0}};
    int shortestDist= std::numeric_limits<int>::max(); 
    int cnt=0; 
    std::unordered_map<std::pair<std::pair<int,int>, char>, std::vector<std::pair<std::pair<int,int>,int>>, nestedPairHash> foundpaths;  
    do{
        std::cout << "run #"<<cnt << " current shortest: "<< shortestDist <<std::endl; 
        for(const char& key: keys){ //Für jeden Zielbuchstaben
            std::cout<< "Doing: "<< key << " with # to find: "<<targets[key]<<std::endl; 
            std::vector<std::pair<std::pair<int,int>,int>> newDist;
            for(int start=0; start<dist.size(); start++){ // Für jeden startpunkt
                std::cout << "Startpunkt #"<<start+1 << "/"<<dist.size() <<std::endl; 
                pos= dist[start].first; 
                int traveled= dist[start].second;
                std::pair<std::pair<int, int>, char> lookupKey {pos, key};
                if(foundpaths.contains(lookupKey)){
                    std::vector<std::pair<std::pair<int,int>,int>> nextDist= foundpaths[lookupKey]; 
                    for(const std::pair<std::pair<int,int>,int>& d: nextDist){
                        newDist.push_back({d.first, d.second + traveled});
                    }
                    continue;
                }
                // auto timerStart = std::chrono::high_resolution_clock::now();
                if(traveled> shortestDist){
                    continue;
                }
                std::vector<std::pair<std::pair<int,int>,int>> nextDist= bfs(map, targets[key], key, pos); //findet jedes Vorkommnis des Buchstabens 
                for(const std::pair<std::pair<int,int>,int>& d: nextDist){
                    newDist.push_back({d.first, d.second + traveled});
                }
                foundpaths.insert({lookupKey, nextDist}); 
                // std::cout <<"travelled: "<<traveled <<std::endl; 
                // for(int target=0; target< targets[key]; target++){ // Alle Vorkommnisse des jeweiligen Buchstabens
                //     auto start = std::chrono::high_resolution_clock::now();
                //     std::cout << "\t doing: "<< target+1 <<"/"<< targets[key]; 
                //     std::pair<std::pair<int,int>,int> nextDist= bfs(map, key, pos);
                //     // std::cout<<"New dist: " << nextDist.second + traveled << " additional: " << nextDist.second<<" travelled: "<<traveled << std::endl;
                //     newDist.push_back({nextDist.first, nextDist.second + traveled});
                //     auto end = std::chrono::high_resolution_clock::now();
                //     std::chrono::duration<double> duration = end - start;
                //     std::cout << " \t Dauer: " << duration.count() << " Sekunden." << std::endl;
                // }
                // auto timerEnd = std::chrono::high_resolution_clock::now();
                // std::chrono::duration<double> duration = timerEnd - timerStart;
                // std::cout << " \t Dauer: " << duration.count() << " Sekunden." << std::endl;
            }
            dist= newDist; 
        }
        // for(const auto& d: dist){
        //     std::cout <<"dist" << d.second<<std::endl; 
        // }
        // Jetzt haben wir in dist die distanzen zu den Endpunkten.
        // Jetzt von jedem Endpunkt zum start zurück:
        // std::cout << "now back to start: "<<std::endl; 
        for(std::pair<std::pair<int,int>,int>& fin: dist){
            pos= fin.first; 
            // std::cout << pos.first <<", "<<pos.second << " With: " << fin.second<<std::endl; 
            std::vector<std::pair<std::pair<int,int>,int>>nextDist= bfs(map,1, 'a', pos);
            if(nextDist[0].second + fin.second < shortestDist){
                shortestDist= nextDist[0].second + fin.second;
            }
            if(nextDist.size()>1){
                std::cout << "zu viele startpunkte gefunden"<<std::endl; 
            }
        }
        // std::cout<<shortestDist <<std::endl; 
        cnt++; 
        dist.clear(); 
        dist.push_back({startpos, 0}); 
    } while(std::next_permutation(keys.begin(), keys.end()));
    
    std::cout <<shortestDist<<std::endl;

    return 0;
}

std::vector<std::pair<std::pair<int,int>, int>> bfs(const std::vector<std::string>& map, const int& anzahl, const char& target, std::pair<int,int>& pos){
    std::vector<std::pair<std::pair<int,int>, int>> results;
    auto timerStart = std::chrono::high_resolution_clock::now();
    std::queue<std::pair<std::pair<int,int>,int>> q;
    q.push({pos, 0});
    int zähler=1; 
    std::unordered_set<std::pair<int,int>, pairHash> visited;
    std::vector<std::pair<int,int>> dirs {{1,0}, {-1,0}, {0,1}, {0,-1}};
    while(!q.empty()){
        std::pair<std::pair<int,int>,int> curr= q.front();
        q.pop(); 
        int currDist = curr.second;
        std::pair<int,int> currPos= curr.first;

        // Wenn hier das gesuchte Zeichen ist:
        if( at(map, currPos)== target){
            // Entferne das zeichen, dass es beim nächsten Durchlauf nicht wieder gefunden wird:
            // at(map, currPos)='.';
            std::cout << "found: "<< zähler;
            auto timerEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = timerEnd - timerStart;
            std::cout << " \t Dauer: " << duration.count() << " Sekunden." << std::endl; 
            results.push_back({currPos, currDist});
            if(zähler == anzahl){
                return results; 
            }
            zähler++; 
        }

        // Position als besucht markieren:
        visited.insert(currPos); 

        for(const std::pair<int,int>& dir: dirs){
            std::pair<int,int> nextPos= currPos + dir;
            if(nextPos.first<0 ){ // Eigentlich kann man nur am Start nach oben raus, sonst ist überall # Rand
                continue;
            }
            char c = at(map, nextPos); 
            if(c == '#' || c== '~'){
                continue;
            }
            if(visited.contains(nextPos)){
                continue;
            }
            // Neue Position in die queue:
            q.push({nextPos, currDist+1});
        }
    }
    return results; 
}