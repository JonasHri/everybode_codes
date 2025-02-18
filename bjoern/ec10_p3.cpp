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
    // ostream& operator<<(ostream&os, const bool& b){
    //     if(b){
    //         os<<"true";
    //     }else{
    //         os<<"false";
    //     }
    //     return os; 
    // }
}; 

int solveOneSquare(std::vector<std::string>& field, int startrow, int startcol);
int count(const std::vector<std::string>& field, int startrow, int startcol);
std::optional<char> findQuestionmark(std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol);
char findSymbol(const std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol);


int main(){
    std::vector<std::string> field;

    std::string line;
    std::fstream file("everybody_codes_e2024_q10_p3.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        field.push_back(line);
    }
    int erg=0; 
    for(int runs=0; runs<10; runs++){
        erg=0; 
        for(int i=0; i<=field.size()-8; i+=6){
            for(int j=0; j<= field.size()-8; j+=6){
                erg+= solveOneSquare(field, i, j);
            }
        }
    }
    std::cout << erg << std::endl; 
    // std::cout << field; 

    return 0; 
}

int solveOneSquare(std::vector<std::string>& field, int startrow, int startcol){
    // Find all symbols excl ? 
    for(int i=startrow+2; i< startrow+6; i++){
        for(int j=startcol+2; j<startcol+6; j++){
            field[i][j]=findSymbol(field, startrow, startcol, i, j);
            // std::cout << "i,j:"<<i<<","<<j<<" neuer Feldeintrag: " <<field[i][j]<<std::endl; 
        }
    }
    // Try to find the ? 
    for(int i=startrow+2; i< startrow+6; i++){
        for(int j=startcol+2; j<startcol+6; j++){
            if(field[i][j]=='#'){
                // std::cout <<"called questionmark method at: "<<i<<","<<j<<std::endl; 
                if(auto missingC= findQuestionmark(field, startrow, startcol, i, j)){
                    field[i][j]= *missingC;
                }
            }
        }
    }
    return count(field, startrow, startcol);
}

int count(const std::vector<std::string>& field, int startrow, int startcol){
    int i=1;
    int count=0; 
    for(int row= startrow+2; row< startrow+6; row++){
        for (int col= startcol+2; col< startcol+6; col++){
            if(field[row][col]=='#'){
                return 0; 
            }
            count += i* (field[row][col]-64);
            i++; 
        }
    }
    // std::cout << count << std::endl; 
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
    // std::cout<<"row,col"<<startrow<<","<<startcol << " incol: "<<isInCol<<" inRow: "<<isInRow<<" remaining pos: "<<remainingPos <<std::endl;
    //  --> positions found correctly 
    if(isInCol==isInRow){
        return std::nullopt; 
    }
    std::vector<int> insides={2,3,4,5};
    bool hasPartner=false;
    char missingC='+';
    bool foundOneMatch=false; 
    if(isInCol){ //if the ? is in the col then 1 symbol in row is unmatched 
        for(const int& border: dirs){
            hasPartner=false; 
            for(const int& inside: insides){
                if(field[pRow][startcol+border]==field[pRow][startcol+inside]){
                    if(foundOneMatch){
                        return std::nullopt;
                    }
                    hasPartner=true;
                    foundOneMatch=true;
                }
            }
            if(!hasPartner){
                missingC=field[pRow][startcol+border];
            }
        }
    }
    if(isInRow){
        for(const int& border: dirs){
            hasPartner=false; 
            for(const int& inside: insides){
                // std::cout<< field[startrow+border][pCol]<<","<<field[startrow+inside][pCol]<<" "<< (field[startrow+border][pCol]==field[startrow+inside][pCol])<<std::endl; 
                if(field[startrow+border][pCol]==field[startrow+inside][pCol]){
                    if(foundOneMatch){
                        return std::nullopt;
                    }
                    hasPartner=true;
                    foundOneMatch=true;
                }
            }
            if(!hasPartner){
                missingC=field[startrow+border][pCol];
                // std::cout <<"hier drin"<<std::endl; 
            }
        }
    }
    // replace ? with new char 
    // std::cout <<"missingC: "<<missingC << std::endl; 
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
// bool stopper=true; 
char findSymbol(const std::vector<std::string>& field, int startrow, int startcol, int pRow, int pCol){
    char c='#';
    std::vector<int> dirs={0,1,6,7};
    for(const int Rowdir: dirs){
        for(const int Coldir: dirs){
            // if(stopper){
            //     std::cout<<"row: "<<field[Rowdir+startrow][pCol]<<" col: "<<field[pRow][Coldir+startcol]<<(field[Rowdir+startrow][pCol]==field[pRow][Coldir+startcol])<<std::endl;
            
            //     // std::cout<<"row: "<<field[Rowdir+startrow][pCol]<<"with row, col "<<Rowdir+startrow<<","<<pCol<<"."<<std::endl;
            //     // std::cout<<"col: "<<field[pRow][Coldir+startcol]<<"with row, col "<<pRow<<","<<Coldir+startcol<<"."<<std::endl; 
            // }
            if(field[Rowdir+startrow][pCol]==field[pRow][Coldir+startcol]){
                c=field[Rowdir+startrow][pCol];
                break;
            }
        }
    }
    // if(stopper){
    //     std::cout << "returned char: "<< c << std::endl; 
    // }
    // stopper=false ;
     
    return c; 
} 