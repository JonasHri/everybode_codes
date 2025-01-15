#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void match(const std::vector<::std::string>& text, std::vector<std::string>& found,  std::string word, int x, int y);
enum dir{
    up=0, right, down, left
};

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
    std::string reversedWord; 
    for(const std::string w: words){
        for(int i=0; i<text.size(); i++){
            for(int j=0; j<text[i].size(); j++){
                if(text[i][j]==w[0]){
                    match(text,found,w,i,j);
                    reversedWord= w;
                    std::reverse(reversedWord.begin(), reversedWord.end());
                    match(reverseText, reversedFound, w, i, j);
                }
            }
        } 
    }
    
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
    
    std::ofstream outfile("out.txt");

    for(const std::string line: text){
        outfile<< line<< std::endl; 
    }
    outfile <<std::endl; 
    for( const std::string line: found){
        outfile<< line<< std::endl;
    }
    outfile.close(); 
    
    return 0; 
}

void match(const std::vector<::std::string>& text, std::vector<std::string>& found,  std::string word, int x, int y){
    //x ist zeile, y ist spalte 
    
    int len=word.length(); 
    bool dir [4] = {}; 
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
/*
    //left 
    for(int i=0; i<len; i++){
        int newY = (y - i) % text[1].length();
        if(text[x][newY]!=word[i]){
            break; 
        }
        if(i==len-1 && text[x][newY]==word[i]){
            dir[left]=true;
        } 
    }

    //right
    for(int i=0; i<len; i++){
        int newY = (y + i) % text[1].length(); 
        if(text[x][newY]!=word[i]){
            break; 
        } 
        if(i==len-1 && text[x][newY]==word[i]){
            dir[right]=true;
        } 
    }

    //up
    for(int i=0; i<len; i++){
        int newX = (x - i); 
        if(newX >=text.size()){
            break;
        }
        if(text[newX][y]!=word[i]){
            break; 
        } 
        if(i==len-1 && text[newX][y]==word[i]){
            dir[up]=true;
        } 
    }

    //down  
    for(int i=0; i<len; i++){
        int newX = (x + i);
        if(newX >=text.size()){
            break;
        }
        if(text[newX][y]!=word[i]){
            break; 
        } 
        //std::cout << "newX: "<< newX << std::endl; 
        if(i==len-1 && text[newX][y]==word[i]){
            dir[down]=true;
        } 
    }

    
    //Abmarkern:
    int xNew=x, yNew=y;
    if (dir[left]){
        for(int i=0; i<len; i++){
            yNew=(y-i)%  text[1].length();
            found[xNew][yNew]='#';
        } 
    }
    if(dir[right]){
        for(int i=0; i<len; i++){
            yNew=(y+i)%  text[1].length();
            found[xNew][yNew]='#';
        } 
    }
    if(dir[up]){
        for(int i=0; i<len; i++){
            xNew=(x-i)% text.size();
            found[xNew][yNew]='#';
        } 
    }
    if(dir[down]){
        for(int i=0; i<len; i++){
            xNew=(x+i)% text.size();
            found[xNew][yNew]='#';
        } 
    }
    return; 
}
*/