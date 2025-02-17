#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

namespace std{
    ostream& operator<<(ostream& os, const vector<string>& vs){
        for(const string& s: vs){
            os<<s<<endl;
        }
        return os;
    }
}; 

int solveOneSquare(std::vector<std::string>& field, int startrow, int startcol);
int count(const std::vector<std::string>& field, int startrow, int startcol);
std::optional<char> findQuestionmark(std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol);
char findSymbol(const std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol);


int main(){
    std::vector<std::string> field;

    std::string line;
    std::fstream file("everybody_codes_e2024_q10_p3_TEST.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        field.push_back(line);
    }
    int erg=0; 
    for(int i=0; i<=field.size()-8; i+=6){
        for(int j=0; j<= field.size()-8; j+=6){
            erg+= solveOneSquare(field, i, j);
        }
    }
    std::cout << erg << std::endl; 
    std::cout << field; 

    return 0; 
}

int solveOneSquare(std::vector<std::string>& field, int startrow, int startcol){
    // Find all symbols excl ? 
    for(int i=startrow+2; i< startrow+6; i++){
        for(int j=startcol+2; j<startcol+6; j++){
            field[i][j]=findSymbol(field, startrow, startcol, i, j);
        }
    }
    // Try to find the ? 
    for(int i=startrow+2; i< startrow+6; i++){
        for(int j=startcol+2; j<startcol+6; j++){
            if(field[i][j]=='#'){
                if(auto missingC= findQuestionmark(field, startrow, startcol, i, j)){
                    field[i][j]= *missingC;
                }
            }
        }
    }
    return  count(field, startrow, startcol);
}

int count(const std::vector<std::string>& field, int startrow, int startcol){
    int i=1;
    int count=0; 
    for(int row= startrow+2; row< startrow+6; row++){
        for (int col= startcol+2; col< startcol+6; col++){
            if(field[row][col]=='#'){
                return 0; 
            }
            count += i* field[row][col]-64;
        }
    }
    return count; 
}


std::optional<char> findQuestionmark(std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol){
    // see if ? is in row or col 
    bool isInRow = false;
    bool isInCol = false;
    int remainingPos=-1;
    std::vector<int> dirs={0,1,6,7};
    for(const int& RowDir: dirs){
        if(field[RowDir+startrow][pCol]=='?'){
            isInCol=true;
            remainingPos=RowDir+startrow;
        }
    }
    for(const int& ColDir: dirs){
        if(field[pRow][ColDir+startcol]=='?'){
            isInRow=true;
            remainingPos=ColDir+startcol;
        }
    }
    if(isInCol==isInRow){
        return std::nullopt; 
    }
    std::vector<int> insides={2,3,4,5};
    bool hasPartner=false;
    char missingC='+';
    if(isInCol){ //if the ? is in the col then 1 symbol in row is unmatched 
        for(const int& border: dirs){
            for(const int& inside: insides){
                if(field[pRow][startcol+border]==field[pRow][startcol+inside]){
                    hasPartner=true;
                    break;
                }
            }
            if(!hasPartner){
                missingC=field[pRow][startcol+border];
            }
        }
    }
    if(isInRow){
        for(const int& border: dirs){
            for(const int& inside: insides){
                if(field[startrow+border][pCol]==field[startrow+inside][pCol]){
                    hasPartner=true;
                    break;
                }
            }
            if(!hasPartner){
                missingC=field[startrow+border][pCol];
            }
        }
    }
    // replace ? with new char 
    if(isInRow){
        field[pRow][remainingPos]= missingC;
    }
    if(isInCol){
        field[remainingPos][pCol]= missingC;
    }
    if(missingC!='+'){
        return missingC;
    }
    return std::nullopt;
}

char findSymbol(const std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol){
    char c='#';
    std::vector<int> dirs={0,1,6,7};
    for(const int Rowdir: dirs){
        for(const int Coldir: dirs){
            if(field[Rowdir+startrow][pCol]==field[pRow][Coldir+startcol]){
                c=field[Rowdir+Rowdir][pCol];
            }
        }
    }
    return c; 
} 