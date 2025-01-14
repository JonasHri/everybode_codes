#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void match(const std::vector<::std::string>& text, std::vector<std::string>& found,  std::string word, int x, int y);


int main(){
    std::vector<std::string> words;
    std::vector<std::string> text;

    std::string line;
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
        }
    }
    std::vector<std::string> found = text; 

    for(const std::string w: words){
        for(int i=0; i<text.size(); i++){
            for(int j=0; j<text[i].size(); j++){
                if(text[i][j]==w[0]){
                    match(text,found,w,i,j);
                }
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

    return 0; 
}

void match(const std::vector<::std::string>& text, std::vector<std::string>& found,  std::string word, int x, int y){
    //x ist zeile, y ist spalte 
    
    int len=word.length(); 
    //std::cout << word << " at: " << x<< ", "<<y <<std:: endl; 
    //left 
    char dir = 'x'; 
    for(int i=0; i<len; i++){
        int newY = (y - i) % text[1].length();
        if(text[x][newY]!=word[i]){
            break; 
        }
        if(i==len-1 && text[x][newY]==word[i]){
            dir='l';
        } 
    }

    //right
    for(int i=0; i<len; i++){
        int newY = (y + i) % text[1].length(); 
        if(text[x][newY]!=word[i]){
            break; 
        } 
        if(i==len-1 && text[x][newY]==word[i]){
            dir='r';
        } 
    }


    //up
    for(int i=0; i<len; i++){
        int newX = (x - i) % text.size(); 
        if(text[newX][y]!=word[i]){
            break; 
        } 
        if(i==len-1 && text[newX][y]==word[i]){
            dir='u';
        } 
    }

    //down
    
    for(int i=0; i<len; i++){
        int newX = (x + i) % text.size();
        if(text[newX][y]!=word[i]){
            break; 
        } 
        //std::cout << "newX: "<< newX << std::endl; 
        if(i==len-1 && text[newX][y]==word[i]){
            dir='d';
        } 
    }

    
    //Abmarkern:
    int xNew=x, yNew=y;
    switch (dir){
        case 'l': for(int i=0; i<len; i++){
            yNew=(y-i)%  text[1].length();
            found[xNew][yNew]='#';
        } 
        break;
        case 'r': for(int i=0; i<len; i++){
            yNew=(y+i)%  text[1].length();
            found[xNew][yNew]='#';
        } 
        break;
        case 'u': for(int i=0; i<len; i++){
            xNew=(x-i)% text.size();
            found[xNew][yNew]='#';
        } 
        break;
        case 'd': for(int i=0; i<len; i++){
            xNew=(x+i)% text.size();
            found[xNew][yNew]='#';
        } 
        break;
    }
    
    return; 
}