#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <queue>

struct point{
    int x, y;
    bool visited {false};
    
    std::size_t operator() () const{
        return std::hash<int>() (x) ^ (std::hash<int>()(y)<<1); 
    }

    bool operator==(const point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator<(const point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    int manhattenAbstand(const point& rhs) const {
        return std::abs(x-rhs.x) + std::abs(y-rhs.y);
    }
};

struct pointHash{
    std::size_t operator()(const point& p)const{
        return std::hash<int>() (p.x) ^ (std::hash<int>()(p.y)<<1);
    }
};

std::ostream& operator<<(std::ostream& os, const point& p){
    os << p.x << ", "<< p.y;
    return os; 
}
struct pairHash{
    template<typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& p) const{
        return std::hash<T>()(p.first) ^ (std::hash<U>()(p.second) << 1);
    }
};
void parseInput(std::fstream& file, std::vector<std::string>& map, std::unordered_set<point, pointHash>& stars){
    if(!file.is_open()){
        std::cerr << "File not found"<<std::endl;
        return; 
    }
    std::string line;
    int currRow=0; 
    while(std::getline(file, line)){
        map.push_back(line);
        for(int i=0; i< line.length(); i++){
            if(line.at(i)=='*'){
                stars.insert({currRow, i});
            }
        }
        currRow++; 
    }
    return; 
}


int MST(std::unordered_set<point, pointHash>& stars){
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> q;
    std::vector<point> points;
    for(point s: stars){
        points.push_back(s);
    }
    q.push({0,0});
    
    int totalWeight=0; 
    while(!q.empty()){
        auto [weight, u]= q.top();
        q.pop();
        if(points[u].visited){
            continue;
        }
        totalWeight += weight;
        points[u].visited=true; 

        for(int v=0; v<points.size(); v++){
            if(!points[v].visited){
                q.push({points[u].manhattenAbstand(points[v]), v}); 
                // std::cout << "pushing: "<< points[v] <<std::endl; 
            }
        }
    }
    return totalWeight; 
}



int main(){
    std::vector<std::string> map;
    std::unordered_set<point, pointHash> stars;
    
    std::fstream file("everybody_codes_e2024_q17_p2.txt");
    parseInput(file, map, stars);
    // int starcount=1; 
    // for(auto it=stars.begin(); it!= stars.end(); it++){
    //     std::cout << starcount++ << ": "<< *it << std::endl; 
    // }

    int erg= MST(stars); 

    std::cout << erg + stars.size() <<std::endl; 

    return 0; 
}