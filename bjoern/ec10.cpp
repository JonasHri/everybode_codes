#include <iostream>
#include <vector>
#include <fstream>
#include <string>

char findPattern(const std::vector<std::string>& field, int i, int j);

int main(){
    std::vector<std::string> field;

    std::string line;
    std::fstream file("everybody_codes_e2024_q10_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        field.push_back(line);
    }

    std::string erg="";
    for(int i=2; i<field.size()-2; i++){
        for(int j=2; j<field[0].size()-2; j++){
            std::cout << "i:"<<i<<" j:"<<j<<std::endl; 
            field[i][j] = findPattern(field, i, j); 
            erg+= (field[i][j]);
        }
    }

    std::cout << erg <<std::endl; 
    return 0; 
}

char findPattern(const std::vector<std::string>& field, int i, int j){
    std::cout << "called fn with: "<<i<<", "<<j<<std::endl; 
    char erg= '#';
    for (char c: field[i]){
        if (c=='.'){
            continue; 
        }
        for(int x=0; x< field.size(); x++){
            char d = field[x][j];
            if(c==d){
                erg=c;
            }
        }
    }
    return erg;
}