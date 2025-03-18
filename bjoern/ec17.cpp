#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <queue>
#include <optional>
#include <algorithm>

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

std::vector<std::vector<point>> findConstellation(std::vector<point>& points){
    std::vector<std::vector<point>> constellations;
    for(point& p: points){
        // if(p.visited){
        //     continue;
        // }
        std::vector<point> constellation; 
        for(const point& p2: points){
            if(p2.visited){
                continue;
            }
            if(p.manhattenAbstand(p2)<6){
                constellation.push_back(p2);
            }
        }
        constellations.push_back(constellation); 
        // p.visited=true; 
    }
    std::sort(constellations.begin(), constellations.end(), [&] (std::vector<point>& a, std::vector<point>& b){return a.size() > b.size(); }); 
    std::vector<std::vector<point>> uniqConstellations; 
    std::unordered_set<point, pointHash> used; 
    std::cout << "es gibt "<<constellations.size() << " Konstellationen "<< std::endl; 
    int i=1; 
    for(auto& constellation: constellations){
        std::cout << "Die "<<i++<<".-te Konstellation hat "<<constellation.size() <<" Sterne "<<std::endl; 
        bool uniq =true; 
        for(point& p: constellation){
            if(used.contains(p)){
                uniq = false; 
                break; 
            }
            used.insert(p); 
        }
        if(uniq){
            uniqConstellations.push_back(constellation); 
        }
    }
    std::cout << "Es gibt davon "<<uniqConstellations.size() <<" einzigartige Konstellationen "<<std::endl; 
    return uniqConstellations; 
}

int brilliantMST(std::vector<point>& points, int start=0){
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> q;
    for(point& p: points){
        p.visited=false; 
    }
    q.push({0,start});
    int starsInconstellation = 0; 
    int totalWeight=0; 
    while(!q.empty()){
        auto [weight, u]= q.top();
        q.pop();
        if(points[u].visited){
            continue;
        }
        totalWeight += weight;
        points[u].visited=true; 
        starsInconstellation++; 

        for(int v=0; v<points.size(); v++){
            if(!points[v].visited){
                q.push({points[u].manhattenAbstand(points[v]), v});
                // std::cout << "pushing: "<< points[v] <<std::endl; 
            }
        }
    }
    return totalWeight + starsInconstellation; 
}

int main(){
    std::vector<std::string> map;
    std::unordered_set<point, pointHash> stars;
    
    std::fstream file("everybody_codes_e2024_q17_p3.txt");
    parseInput(file, map, stars);
    // int starcount=1; 
    // for(auto it=stars.begin(); it!= stars.end(); it++){
    //     std::cout << starcount++ << ": "<< *it << std::endl; 
    // }
    std::vector<point> points;
    for(point s: stars){
        points.push_back(s);
    }

    int erg=0;
    int l1{0}, l2{0}, l3{0};  
    std::vector<std::vector<point>> constellations= findConstellation(points);
    // for(auto& c: constellations){
    //     std::cout << c.size() <<std::endl; 
    // }
    for(auto constellation: constellations){
        int curr = brilliantMST(constellation); 
        // std::cout << "From: " <<points[i]<<": "<<curr <<std::endl; 
        if(curr>l1){
            l3=l2;
            l2=l1;
            l1=curr;
        } else if(curr>l2){
            l3=l2;
            l2=curr;
        } else if(curr>l3){
            l3=curr;
        }
    }

    std::cout << l1 <<", " <<l2<< ", "<<l3 <<std::endl; 

    erg= l1*l2*l3; 

    std::cout << erg<<std::endl; 

    return 0; 
}