#include <iostream>
#include <vector>
#include <fstream>
#include <string>

namespace std{
    ostream& operator<<(ostream& os, const vector<string>& vs){
        for(const string& s: vs){
            os << s << endl;
        }
        return os; 
    }
}

char findPattern(const std::vector<std::string>& field, int i, int j);
char findPattern_p2( std::vector<std::string>& field, int x, int y, size_t row, size_t col);
int calcWholeMap( std::vector<std::string>& field);
int oneWord( std::vector<std::string>& field, size_t row, size_t col);
int patternToPower(char&& c); 
void questionmark(std::vector<std::string>& field, size_t col, size_t row);



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

    // for(const std::string& str: field){
    //     std::cout << str<<std::endl; 
    // }
    // std::string erg="";
    // for(int i=2; i<field.size()-2; i++){
    //     for(int j=2; j<field[0].size()-2; j++){
    //         std::cout << "i:"<<i<<" j:"<<j<<std::endl; 
    //         field[i][j] = findPattern(field, i, j); 
    //         erg+= (field[i][j]);
    //     }
    // }
    std::cout << field << std::endl;
    int erg= calcWholeMap(field); 
    std::cout << erg <<std::endl; 
    std::cout << field <<std::endl; 

    return 0; 
}

int calcWholeMap(std::vector<std::string>& field){
    int erg=0; 
    for(size_t row=0; row<=field.size()-8; row+=6){
        // std::cout << field[row] <<std::endl; 
        for(size_t col=0; col<= field[row].length()-8; col+=6){
            erg+= oneWord(field, row, col);
            break;
            // std::cout<< "row/max: " << row <<"/"<<field.size() << ", col/max: "<<col <<"/"<<field[row].length()<< std::endl; 
        }
        break;
    }
    for(size_t row=0; row<=field.size()-8; row+=6){
        for(size_t col=0; col<= field[row].length()-8; col+=6){
            questionmark(field, row, col);
            break;
        }
        break;
    }
    return erg; 
}

int oneWord(std::vector<std::string>& field, size_t row, size_t col){
    int erg=0;
    int cnt=1; 
    for(int i=row+2; i<row+6; i++){
        for(int j=col+2; j<col+6; j++){
            // std::cout << i<<","<<j <<std::endl; 
            erg+= cnt* patternToPower(findPattern_p2(field, i, j, col, row));
            cnt++; 
        }
    }

    return erg; 
}

int patternToPower(char&& c){
    int erg= c- 64;
    // std::cout<< c<<":"<<erg <<std::endl;
    return erg;
}

void questionmark(std::vector<std::string>& field, size_t row, size_t col){
    char erg='#';
    char c;
    int zeileD, zeileQ, spalteD, spalteQ; 
    for(int i=row; i<row+8; i++){
        for(int j=col; j<col+8; j++){
            if(field[i][j]=='?'){
                if(i<2+row || i>6+row){
                    for(int k= col+2; k<col+6; k++){
                        if(field[i][k]=='#'){
                            zeileD= i;
                            spalteD=k;
                            zeileQ=i;
                            spalteQ=j;
                        
                        }
                    }
                } else{
                    for(int k=row; k< row+6; k++){
                        if(field[k][j]=='#'){
                            zeileD= k;
                            spalteD=j;
                            zeileQ =i;
                            spalteQ=j;
                        }
                    }
                }
            }
        }
    }
    std::cout << "hier"<<std::endl; 

    std::vector<int> pos={0,1,6,7};
    char replacer='+';
    if(zeileD==zeileQ){
        for(const int& p: pos ){
            int rand = col+p;
            for(int i=col+2; i<col+6; i++){
                if(field[zeileD][rand]==field[zeileD][i]){
                    break;
                }
                replacer=field[zeileD][rand];
            }
        }
    } else{
        for(const int& p: pos ){
            int rand = row+p;
            for(int i=row+2; i<row+6; i++){
                if(field[zeileD][rand]==field[zeileD][i]){
                    break;
                }
                replacer=field[zeileD][rand];
            }
        }
    }
    std::cout << zeileQ<<","<<spalteQ<<std::endl; 

    field[zeileQ][spalteQ]=replacer; 
    std::cout << "hier"<<std::endl; 

}

char findPattern_p2(std::vector<std::string>& field, int x, int y, size_t row, size_t col){
    char erg='#';
    for(size_t i=row; i<row+8; i++){
        char c = field[i][y];
        if(c=='.' || c=='#'){
            continue;
        }
        for(size_t j=col; j<col+8; j++){
            char d= field[x][j];
            std::cout << "c,d: "<<c<<", "<<d<<" at: "<<i<<","<<y<<" and: "<< x<<", "<<j; 
            if(c==d){
                std::cout <<"found "<<c <<std::endl; 
                erg=c;
                break;
            }
            std::cout <<std::endl; 
        }
    }
    field[x][y]=erg; 
    return erg; 
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

