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

std::optional<std::pair<int,int>> findPos(const std::vector<std::string>& map, const char& c='S');
int heightdiff(const int& a, const int& b);
int bfs(std::vector<std::string>& map, std::pair<int,int> startpos);


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

    int tmp = heightdiff(9,3);
    std::cout << tmp << std::endl; 

    return 0;
}

struct Plattform{
    int m_x, m_y; //coordinates 
    int m_dist; //distance to this Plattform 
    int m_height; 
    bool m_visited;
    Plattform* m_prev = nullptr; 

    Plattform(const std::vector<std::string>& map, int x, int y, int dist, int height=-1)
    :m_x(x), m_y(y), m_dist(dist), m_visited(false)
    {
        if(height=-1)
            m_height= map[x][y] -'0';
        else 
            m_height=height; 
    };
    Plattform(const std::vector<std::string>& map, std::pair<int,int> coords, int dist, int height=-1)
    :m_x(coords.first), m_y(coords.second), m_dist(dist), m_visited(false)
    {
        if(height=-1)
            m_height= map[coords.first][coords.second] -'0';
        else 
            m_height=height; 
    };
    Plattform(const std::vector<std::string>& map, int x, int y)
    : m_x(x), m_y(y), m_height(map[x][y]), m_visited(false), m_dist(std::numeric_limits<int>::max()-1)
    {
    }
    Plattform(int x, int y)
    :m_x(x), m_y(y), m_height(std::numeric_limits<int>::max()), m_dist(std::numeric_limits<int>::max()), m_visited(true)
    {
    }
    bool operator()(const Plattform& a, const Plattform& b){
        return a.m_dist > b.m_dist; 
    }
}; 

// Plattform operator+(const Plattform& a, const std::pair<int,int>& b){
//     int x = a.m_x + b.first;
//     int y = a.m_y + b.second;


// }

int dijkstra(std::vector<std::string>& map, std::pair<int,int> startpos){
    std::vector<std::vector<Plattform>> dist; 
    for(int i=0; i< map.size(); i++){
        for(int j=0; j<map[i].length(); j++){
            char c= map[i][j];
            if(c>='0' && c<='9'){
                dist[i][j]= Plattform(map, i, j);
            }
            else{
                dist[i][j]= Plattform(i,j); 
            }
        }
    }
    std::priority_queue<Plattform> q;
    q.emplace(map, startpos, 0,0);
    std::vector<std::pair<int,int>> dirs={
        {1,0}, {0,1}, {-1,0}, {0,-1} 
    };
    while(!q.empty()){
        Plattform curr= q.top();
        q.pop();
        int x= curr.m_x, y=curr.m_y; 
        for(auto dir: dirs){
            
        }
    }

}


int bfs(std::vector<std::string>& map, std::pair<int,int> startpos){
    std::queue<Plattform> q;
    q.emplace(map, startpos.first, startpos.second, 0, 0);

    std::vector<std::pair<int,int>> dirs={
        {1,0}, {0,1}, {-1,0}, {0,-1} 
    };
    while(!q.empty()){
        Plattform curr = q.front();
        int currheight= curr.m_height;
        q.pop();
        // for(auto dir: dirs){
        //     Plattform nextpos= curr + dir; 



        //     // if(map[nextpos.first][nextpos.second]=='#'){
        //     //     continue;
        //     // }
        //     // int nextheight=map[nextpos.first][nextpos.second] -'0';
        //     // int diff= heightdiff(currheight, nextheight);

        // }
    }
    return 0;
}

int heightdiff(const int& a, const int& b){
    // Wir haben folgende Fälle: gleiche Zahl, a kleiner, a größer
    // Wenn a kleiner, dann kann die differenz b-a kleiner sein, oder die differenz a+10-b
    //  analoge fälle, wenn b kleiner ist (also a größer)
    // sei a der vorgänger, dann muss b verändert werden. 
    if(a==b){
        return 0;
    }
    if(a<b){
        int t1 = std::abs(a-b);
        int t2= std::abs(a+10-b);
        if(std::min(t1, t2)==t1){
            return a-b;
        }
        else{
            return a+10-b; 
        }    
    }
    else{
        int t1 = std::abs(a-b);
        int t2= std::abs(b+10-a);
        if(std::min(t1, t2)==t1){
            return a-b;
        }
        else{
            return -(b+10-a); 
        }    
    }
}


std::optional<std::pair<int,int>> findPos(const std::vector<std::string>& map, const char& c){
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<map[i].length(); j++){
            if(map[i][j]==c){
                return std::make_pair(i, j);
            }
        }
    }
    return std::nullopt; 
}