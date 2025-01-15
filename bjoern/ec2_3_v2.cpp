#include <vector>
#include <iostream>
#include <string>
#include <fstream>

void match(const std::vector<std::string>& text, std::vector<std::string>& found, const std::string& word);


int main(){
    std::vector<std::string> words;
    std::vector<std::string> text;

    std::string line;
    std::fstream file("everybody_codes_e2024_q02_p3.txt");
    if(!file.is_open()){
        std::cerr << "file not found"<<std::endl;
        return 1;
    }
    std::getline(file, line);
    line= line.substr(6);
    size_t sep= line.find(',');
    while(sep!= std::string::npos){
        words.push_back(line.substr(0,sep));
        line= line.substr(sep+1);
        sep=line.find(',');
    }
    words.push_back(line); 
    while(std::getline(file, line)){
        text.push_back(line);
    }

    std::vector<std::string> found= text;

    for(const std::string word: words){
        match(text, found, word);
    }

    int result=0;
    for(const std::string l: found){
        for(const char c: l){
            if (c=='#'){
                result ++;
            }
        }
    }
    std::cout << result <<std::endl; 

    std::ofstream outfile("out2.txt");
    for(const std::string& l: found){
        outfile << l << std::endl; 
    }
    outfile.close();
    return 0; 
}

void match(const std::vector<std::string>& text, std::vector<std::string>& found, const std::string& word){
    for(int x=0; x<text.size(); x++){
        for(int y=0; y<text[x].length(); y++){
            if(text[x][y]!=word[0]){
                continue; 
            }
            //vorwärts      
            for(int dir=0; dir<2; dir++){
                bool hit=true; 
                for(int i=0; i<word.length(); i++){
                    int Xnew = x + i * dir; 
                    int Ynew= (y + i*(1-dir)) % text[x].length();
                    if(Xnew >= text.size() || text[Xnew][Ynew]!= word[i]){
                        hit= false; 
                        break; 
                    }
                }
                if(hit){
                    for(int i=0; i<word.length(); i++){
                        int Xnew = x + i * dir; 
                        int Ynew= (y + i*(1-dir)) % text[x].length();
                        found[Xnew][Ynew]='#';
                        //std::cout << "wort: "<< word << ", Buchstabe: "<< word[i] << ", ZeichenNummer: "<< i <<std::endl; 
                    }
                }
            }
            //rückwärts
            
            for(int dir=0; dir<2; dir++){
                bool hit= true; 
                for(int i=0; i< word.length(); i++){
                    int Xnew= x - i*dir;
                    int Ynew= (y - i*(1-dir)) % text[x].length();
                    if(Xnew<0 || text[Xnew][Ynew]!= word[i]){
                        hit=false;
                        break; 
                    }
                }
                if(hit){
                    for(int i=0; i< word.length(); i++){
                        int Xnew= x - i*dir;
                        int Ynew= ((y - i*(1-dir)) + text[x].length()) % text[x].length();
                        found[Xnew][Ynew]='#';
                    }
                } 
            }
        }
    }
}