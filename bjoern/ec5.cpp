#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

namespace std{
    ostream& operator<<(ostream& os, const std::vector<int>& r){
        for(const int& i: r){
            os << i << " ";
        }
        return os; 
    }
    ostream& operator<<(ostream& os, const std::vector<std::vector<int>>& r){
        int maxcol=0;
        for(int i=0; i< r.size(); i++){
            if(r[i].size() >maxcol){
                maxcol = r[i].size(); 
            }
        }
        for (int i=0; i< maxcol; i++){
            for (int j=0;j< r.size(); j++){
                if(i>=r[j].size()){
                    os << "\t";
                }else{
                    os << r[j][i] << "\t";
                }
            }
            os << std::endl; 
        }
        return os;
    }
     
}

std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>>& m){
    int rows =m.size();
    int cols= m[0].size();
    std::vector<std::vector<int>> transposed(cols, std::vector<int>(rows));
    for(size_t i=0; i<rows; i++){
        for(size_t j=0; j<cols; j++){
            transposed[j][i]=m[i][j]; 
        }
    } 
    return transposed; 
}

void dance(std::vector<std::vector<int>>& map, const int& turn);
void shout(const std::vector<std::vector<int>>& map);

int main(){
    std::vector<std::vector<int>> map; 

    std::fstream file("everybody_codes_e2024_q05_p1.txt");
    std::string line; 
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::vector<int> row; 
        int a;
        while(ss >> a){
            row.push_back(a);
        }
        map.push_back(row);
    }

    std::vector<std::vector<int>> m= transpose(map);
    
    for(int i=1; i<=10; i++){
        dance(m, i);
        shout(m); 
    }


    return 0; 
}

void shout(const std::vector<std::vector<int>>& map){
    for(const std::vector<int> col: map){
        std::cout << col[0];
    }
    std::cout<< std::endl; 
}

void dance(std::vector<std::vector<int>>& map, const int& turn){
    int startPos = (turn-1)%map.size();
    int dancer = map[startPos][0];
    int dancingCol = (startPos+1) % map.size(); 
    map[startPos].erase(map[startPos].begin());
    auto it = map[dancingCol].begin();
    int dir= 1; 
    for(int i=1; i< dancer; i++){
        if(it== map[dancingCol].end()){
            dir=-1;
        }
        it += dir; 
    }
    map[dancingCol].insert(it ,dancer);

}