#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <cmath>

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
long shout(const std::vector<std::vector<int>>& map);

int main(){
    std::vector<std::vector<int>> map; 

    std::fstream file("everybody_codes_e2024_q05_p3.txt");
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
    
    std::unordered_map<int,int> counter; 
    //std::cout <<m<<std::endl; 
    std::cout  << log10(10)<<" na"<<std::endl;

    int i=1;
    long maxVal=0;
    while(true) {
        dance(m, i);
        long shoutet= shout(m); 
        counter[shoutet]++; 
        if(counter[shoutet] ==10000){
            std::cout << "ßöööß: "<< shoutet << " "<< shoutet * i << std::endl; //beginnt mit einer 2 das erg
            std::cout << maxVal << std::endl;
            break; 
        }
        if (shoutet > maxVal){
            maxVal = shoutet;
        }
        // std::cout << i<<": "<< shoutet << " "<< counter[shoutet] <<std::endl; 
        // if(i==10){
        //     break; 
        // }
        i++; 
    }


    return 0; 
}

long shout(const std::vector<std::vector<int>>& map){
    long erg=0;
    for(int i=0; i< map.size(); i++){
        if(erg!=0){
            int len = log10(map[i][0])+1; 
            erg *= std::pow(10, len);
        } 
        erg += map[i][0]; 
    }
    //std::cout<< std::endl;  
    return erg; 
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
        } else if(it== map[dancingCol].begin() && i!=1){
            dir=1; 
        }
        it += dir; 
    }
    map[dancingCol].insert(it ,dancer);

}