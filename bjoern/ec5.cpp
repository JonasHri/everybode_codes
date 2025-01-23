#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace std{
    ostream& operator<<(ostream& os, const std::vector<int>& r){
        for(const int& i: r){
            os << i << " ";
        }
        return os; 
    }
    ostream& operator<<(ostream& os, const std::vector<std::vector<int>>& r){
        for (int i=0; i< r[0].size(); i++){
            for (int j=0;j< r.size(); j++){
                os << r[j][i] << "\t";
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
     
    std::cout << m;

    return 0; 

}

void dance(std::vector<std::vector<int>>& map, const int& turns){
    int dancer = map[0][0];
    int colToDance= map.size();

}