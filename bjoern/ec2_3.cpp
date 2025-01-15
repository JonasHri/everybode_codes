#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void match(const std::vector<::std::string>& text, std::vector<std::string>& found, const std::string& word, int x, int y);

int main(){
    std::vector<std::string> words;
    std::vector<std::string> text;
    std::vector<std::string> reverseText;

    std::string line;
    std::string reversedLine;
    std::fstream file("everybody_codes_e2024_q02_p3.txt");
    if(!file.is_open()){
        std::cerr << "file not found"<<std::endl;
    }

    while(std::getline(file, line)){
        if(line.find(':')!=std::string::npos){
            std::string sub= line.substr(6);
            size_t sep = sub.find(',');
            std::string word;
            while (sep!=std::string::npos){
                word= sub.substr(0, sep);
                words.push_back(word);
                sub=sub.substr(sep+1);
                sep= sub.find(',');
            }
            words.push_back(sub);
        }
        else{
            text.push_back(line);
            reversedLine=line;
            std::reverse(reversedLine.begin(), reversedLine.end());
            reverseText.push_back(reversedLine);
        }
    }
    std::vector<std::string> found = text;
    std::reverse(reverseText.begin(), reverseText.end());
    std::vector<std::string> reversedFound= reverseText;
    for(const std::string w: words){
        for(int i=0; i<text.size(); i++){
            for(int j=0; j<text[i].size(); j++){
                match(text,found,w,i,j);
                match(reverseText, reversedFound, w, i, j);
            }
        } 
    }
    std::vector<std::string> reversedFound2=reversedFound;
    std::reverse(reversedFound.begin(), reversedFound.end());
    for(std::string line: reversedFound){
        std::reverse(line.begin(), line.end());
    }
    for(int i=0; i<found.size(); i++){
        for(int j=0; j<found[i].length(); j++){
            if(reversedFound[i][j]=='#'){
                found[i][j]='#';
            }
        }
    }
    
    int cnt=0; 
    for(const std::string line: found){
        for(const char c: line){
            if(c=='#'){
                cnt++;
            }
        }
    }
    std::cout<< cnt << std::endl; 
    

    //Debug output to file 
    std::ofstream outfile("out.txt");
    outfile << "original Input: "<<std::endl;
    for(const std::string line: text){
        outfile<< line<< std::endl; 
    }
    outfile << "\n das reverste: "<<std::endl; 
    for(const std::string line: reversedFound2){
        outfile << line<<std::endl; 
    }

    outfile << "\n hier das gesamte Ergebnis: "<<std::endl; 
    for( const std::string line: found){
        outfile<< line<< std::endl;
    }
    outfile.close(); 
    
    return 0; 
}

void match(const std::vector<::std::string>& text, std::vector<std::string>& found, const std::string& word, int x, int y){
    //x ist zeile, y ist spalte 
    
    int len=word.length(); 
    //std::cout << word << " at: " << x<< ", "<<y <<std:: endl;

    for(int dir=0; dir<2; dir++){
        bool correct = true;
        for(int i=0; i<len; i++){
            int newX = x+i*dir;
            int newY = (y +i*(1-dir))%text[1].length();
            if(newX >=text.size() || text[newX][newY]!= word[i]){
                correct= false;
                break;
            } 
        }
        if(correct){
            for(int i=0; i<len; i++){
                int newX = x+i*dir;
                int newY = (y +i*(1-dir))%text[1].length();
                found[newX][newY]='#';
            }
        }
    }
    return;
}