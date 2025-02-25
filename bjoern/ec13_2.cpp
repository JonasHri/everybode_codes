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

std::optional<std::pair<int,int>> findPos(const std::vector<std::string>& map, const char& c='S');
int calcHeightDiff(const int& prev, const int& curr);
void calcNextDist(const std::vector<std::string>& map, std::vector<std::vector<int>>& dists, int row, int col);
int calcPath(std::vector<std::string>& map, std::vector<std::vector<int>>& dists, std::pair<int,int> pos);
int calcPath2(std::vector<std::string>& map, std::vector<std::vector<int>>& dists, std::pair<int,int> startPos); 
int iterateThroughBorder(const std::vector<std::string>& map, const std::vector<std::vector<int>>& dists); 


namespace std{
    ostream& operator<<(ostream& os, const std::vector<std::string>& vs){
        for(const string& s: vs){
            os << s <<endl;
        }
        return os; 
    }
    ostream& operator<<(ostream& os, const std::vector<vector<int>>& vi){
        for(const vector<int>& row: vi){
            for(const int& val: row){
                if(val== std::numeric_limits<int>::max()-10){
                    os << "# ";
                } else{
                    os << val << " ";
                }
            }
            os << endl;
        }
        return os; 
    }
    ostream& operator<<(ostream& os, const std::pair<int,int>& pi){
        os << pi.first <<", "<<pi.second; 
        return os; 
    }
}

int main(){
    std::vector<std::string> map; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q13_p3.txt");
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

    // if(auto goal= findPos(map, 'E')){
    //     std::cout << *goal <<std::endl; 
    // }
    // std::cout << map << std::endl; 


    // make int vector for distances 

    std::vector<std::vector<int>> dists(map.size(), std::vector<int>(map[0].size(), std::numeric_limits<int>::max()-10));

    // dists[startpos.first][startpos.second]=0;

    // std::cout << map << std::endl; 
    // int erg= calcPath2(map, dists, startpos);
    int erg = iterateThroughBorder(map, dists);
    std::cout << erg << std::endl; 

    // std::cout << dists<< std::endl; 

    return 0; 
}

int iterateThroughBorder(const std::vector<std::string>& map, const std::vector<std::vector<int>>& dists){
    int shortest= std::numeric_limits<int>::max(); 
    for(int i=1; i< map.size()-1; i++){
        std::vector<std::string> visited= map; 
        std::vector<std::vector<int>> dis = dists;
        dis[i][0]=0;
        int tmp1=calcPath2(visited, dis, std::make_pair(i, 0));
        visited=map;
        dis= dists; 
        dis[i][map[0].length()-1]=0;
        int tmp2=calcPath2(visited, dis, std::make_pair(i, map[0].length()-1)); //-2, weil mein testdiung irgndwie ein leeren eintrag
        // std::cout << "wir starten bei col: "<< map[0].length()-1 <<std::endl; 
        // std::cout << "map size: "<<map.size() <<" und: "<< map[0].size() <<std::endl; 
        // for(int i=0; i< map[0].size(); i++){
        //     std::cout << i<<": "<<map[1][i] <<", ";
        //     if(map[1][i]=='\0'){
        //         std::cout<<"juhuuuuuuuuuu"; 
        //     } 
        // }
        // std::cout << std::endl; 
        // std::cout << dis; 
        // std::cout << tmp1 << "\n" <<std::endl; 
        // if(tmp1<0){
        //     std::cout << tmp1 << " at: "<< i <<", 0"<<std::endl; 
        // }
        // if(tmp2<0){
        //     std::cout << tmp2 << " at: "<< i <<", "<<map[0].length()-1<<std::endl; 
        // }
        if(tmp1<shortest){
            shortest=tmp1;
        }
        if(tmp2<shortest){
            shortest=tmp2;
        }
    }
    for(int i=1; i<map[0].length()-1; i++){
        std::vector<std::string> visited= map; 
        std::vector<std::vector<int>> dis = dists;
        dis[0][i]=0; 
        int tmp1=calcPath2(visited, dis, std::make_pair(0, i));
        visited=map;
        dis= dists;
        dis[map.size()-1][i]=0; 
        int tmp2=calcPath2(visited, dis, std::make_pair(map.size()-1, i));
        if(tmp1<shortest){
            shortest=tmp1;
        }
        if(tmp2<shortest){
            shortest=tmp2;
        }
    }
    return shortest; 
}

int calcPath2(std::vector<std::string>& map, std::vector<std::vector<int>>& dists, std::pair<int,int> startPos){
    std::priority_queue<std::pair<int, std::pair<int, int>>, 
                    std::vector<std::pair<int, std::pair<int, int>>>, 
                    std::greater<std::pair<int, std::pair<int, int>>>> q;
    q.push({0, startPos});
    std::vector<std::pair<int, int>> dirs={ {0,1}, {1,0}, {-1,0}, {0,-1} };
    if(map[startPos.first][startPos.second]=='#'){
        std::cout<<startPos.first<<"/"<<map.size()<<", "<<startPos.second<<"/"<<map[0].size()<<std::endl; 
        return  std::numeric_limits<int>::max() ;
    }
    while(!q.empty()){
        std::pair<int,int> currPos = q.top().second;
        // std::cout << "Visiting: "<< currPos.first<<", "<< currPos.second << std::endl; 
        int currDist= q.top().first; 
        q.pop();
        if(map[currPos.first][currPos.second]=='E'){
            return dists[currPos.first][currPos.second]; 
        }
        for(const auto& dir: dirs){
            int x= currPos.first+ dir.first;
            int y= currPos.second+dir.second;
            if(x<0 || y<0 || x>= map.size() || y>= map[0].length()){
                continue;
            }
            if(map[x][y]=='#'){
                continue;
            }
            //  für part3: nicht aufm rand umher eiern:
            if(x==0 || y==0 || x==map.size()-1 || y==map[0].length()-1 ){ //TODO: hier -2, wegen testding 
                continue; 
            }
            int prevheight= map[currPos.first][currPos.second] - '0';
            if(map[currPos.first][currPos.second]=='S' || map[currPos.first][currPos.second]=='E' || map[currPos.first][currPos.second]=='\r'){
                prevheight=0; 
            }
            if(prevheight<0){
                std::cout << map[currPos.first][currPos.second] << " @ "<<currPos.first<<", "<<currPos.second <<std::endl; 
            }
            int currheight= map[x][y] -'0';
            if(map[x][y]=='S' || map[x][y]=='E' || map[x][y]=='\r'){ //irgendwie sind da irgendwo diese carriage return dinger drin x.x
                currheight= 0; 
            }
            int newDist = dists[currPos.first][currPos.second] + calcHeightDiff(prevheight, currheight) + 1;
            if(calcHeightDiff(prevheight, currheight)> 10){
                std::cout << calcHeightDiff(prevheight, currheight) <<" with: "<< prevheight << ", "<<currheight <<std::endl; 
                std::cout << "prevheight: "<< prevheight<< " map pos: "<< currPos.first<<" "<<currPos.second<<std::endl;
                std::cout << "currheight: "<< currheight<<" map pos: "<<x<<" "<<y <<std::endl; 

            }
            if (newDist < dists[x][y]) {
                if(newDist <0){
                    std::cout <<"illegal value encountered: " <<newDist <<" at: " << startPos<<std::endl;
                    std::cout << dists[currPos.first][currPos.second] << ", "<<calcHeightDiff(prevheight, currheight)<<std::endl; 
                    continue;
                }
                dists[x][y] = newDist;
                if (map[x][y] == '#') {
                    std::cout << "WARNING: Trying to push '#' into queue at (" << x << ", " << y << ")" << std::endl;
                }
                q.push({newDist, {x, y}});
            } 
        }
        // map[currPos.first][currPos.second] = '#'; 
    }
    return std::numeric_limits<int>::max() ; 
}



int calcPath(std::vector<std::string>& map, std::vector<std::vector<int>>& dists, std::pair<int,int> pos){
    int row= pos.first, col= pos.second; 
    if(map[row][col]=='E'){
        return dists[row][col];
    }
    calcNextDist(map, dists, row, col);
    std::vector<std::pair<int, int>> dirs={ {0,1}, {1,0}, {-1,0}, {0,-1} };
    int minValue = std::numeric_limits<int>::max(), minX=-1, minY=-1;
    std::cout << "At: "<<row<<", "<<col<<": "<<dists[row][col]<< " with map num: "<<map[row][col]<<std::endl; 
    for(const auto& dir: dirs){
        int x= row+ dir.first;
        int y= col+dir.second;
        if(x<0 || y<0 || x>= map.size() || y>= map[0].length()){
            continue;
        }
        if(map[x][y]=='#'){
            continue;
        }
        std::cout << "\t visiting: "<<x<<", "<<y<<": "<<dists[x][y]<<std::endl; 
        if(dists[x][y]< minValue){
            minX=x;
            minY=y;
            minValue=dists[x][y];
            
        }
    }
    if (minX == -1 || minY == -1) {
        return -1;
    }
    map[row][col]='#'; 
    return calcPath(map, dists, std::make_pair(minX,minY));
}

void calcNextDist(const std::vector<std::string>& map, std::vector<std::vector<int>>& dists, int row, int col){
    std::vector<std::pair<int, int>> dirs={ {0,1}, {1,0}, {-1,0}, {0,-1} };
    for (const auto& dir:dirs){
        int x= row+ dir.first;
        int y= col+dir.second;
        if(x<0 || y<0 || x>= map.size() || y>= map[0].length()){
            continue;
        }
        if(map[x][y]=='#'){
            continue;
        }
        int prevheight= map[row][col] -'0';
        if(map[row][col]=='S' || map[row][col]=='E'){
            prevheight=0; 
        }
        int currheight= map[x][y] -'0';
        if(map[x][y]=='S' || map[x][y]=='E'){
            currheight= 0; 
        }
        dists[x][y] = std::min(dists[x][y], dists[row][col] + calcHeightDiff(prevheight, currheight) + 1); 
        //alter wert+ höhen diff + 1 um den schritt drauf mitzuzählen 
    }
}

int calcHeightDiff(const int& prev, const int& curr){
    if(prev==curr){
        return 0;
    }
    if(prev<curr){
        int t1 = std::abs(prev-curr);
        int t2= std::abs(prev+10-curr);
        if(std::min(t1, t2)==t1){
            return t1;
        }
        else{
            return t2; 
        }
    } else{
        int t1 = std::abs(prev-curr);
        int t2= std::abs(curr+10-prev);
        if(std::min(t1, t2)==t1){
            return t1;
        }
        else{
            return t2; 
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