#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <limits>
#include <optional>
#include <queue>
#include <clocale>
#include <algorithm>

namespace std{
    std::pair<int,int> operator+(const std::pair<int,int>& a, const std::pair<int,int>& b){
        return std::make_pair(a.first+b.first, a.second+b.second);
    }
}

int main(){
    std::vector<std::string> map; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q11_p3.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        map.push_back(line);
    }
    std::pair<int,int> startpos;
    if(auto tmp= findPos(map)){
        startpos=*tmp;
    } else{
        std::cerr << "no startingposition found"<<std::endl;
        return 1;
    }

    

    return 0;
}

struct plattform{
    int m_x, m_y; //coordinates 
    int m_dist; //distance to this plattform 
    int m_height; 
    bool m_visited;

    plattform(const std::vector<std::string>& map, int x, int y, int dist, int height=-1): m_x(x), m_y(y), m_dist(dist), m_visited(false){
        if(height=-1)
            m_height= map[x][y] -'0';
        else 
            m_height=height; 
    };

}; 

plattform operator+(const plattform& a, const std::pair<int,int>& b){
    
}

int bfs(std::vector<std::string>& map, std::pair<int,int> startpos){
    std::queue<plattform> q;
    q.emplace(map, startpos.first, startpos.second, 0, 0);

    std::vector<std::pair<int,int>> dirs={
        {1,0}, {0,1}, {-1,0}, {0,-1} 
    };
    while(!q.empty()){
        plattform curr = q.front();
        int currheight= curr.m_height;
        q.pop();
        for(auto dir: dirs){
            plattform nextpos= curr + dir;
            if(map[nextpos.first][nextpos.second]=='#'){
                continue;
            }
            int nextheight=map[nextpos.first][nextpos.second] -'0';
            int diff= heightdiff(currheight, nextheight);

        }
    }
}

int heightdiff(const int& a, const int& b){
    // Wir haben folgende Fälle: gleiche Zahl, a kleiner, a größer
    // Wenn a kleiner, dann kann die differenz b-a kleiner sein, oder die differenz a+10-b
    //  analoge fälle, wenn b kleiner ist (also a größer)
    if(a==b){
        return 0;
    }
    if(a<b){
        return std::min(b-a, a+10-b);
    } else{
        return std::min(a-b, b+10-a);
    }
}


std::optional<std::pair<int,int>> findPos(const std::vector<std::string>& map, const char& c='S'){
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[i].length(); j++){
            if(map[i][j]==c){
                return std::make_pair(i, j);
            }
        }
    }
    return std::nullopt; 
}