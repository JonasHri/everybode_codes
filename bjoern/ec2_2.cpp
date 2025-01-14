#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(){
    std::vector<std::string> words;
    std::vector<std::string> text;

    std::string line;
    std::fstream file("everybody_codes_e2024_q02_p2.txt");
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

    int occurances=0; 
    size_t pos; 
    int tmp; 
    
    std::vector<std::string> wordsReverse;
    for(const std::string w: words){
        std::string copy(w);
        std::reverse(copy.begin(), copy.end());
        wordsReverse.push_back(copy);
    }


    for(const auto t: text){
        std::string found = t;  
        std::string textReverse (t);
        std::reverse(textReverse.begin(), textReverse.end());
        std::string foundReverse (textReverse);

        for(const auto w:words){
            pos=0;
            while((tmp= t.find(w,pos))!= std::string::npos){
                for(int i=tmp; i< tmp+w.length(); i++ ){
                    found[i]= '#';
                }
                pos=tmp + w.length();
            }
            pos=0;
            while((tmp= textReverse.find(w,pos))!= std::string::npos){
                for(int i=tmp; i< tmp+w.length()  ; i++ ){
                    foundReverse[i]= '#';
                }
                pos=tmp + w.length();
            }
        }
        std::reverse(foundReverse.begin(), foundReverse.end());
        for(int i=0; i<found.length(); i++){
            if(found[i]=='#' || foundReverse[i]=='#'){
                occurances++;
            }
        }
        //std::cout << found << ": " <<occurances <<std::endl; 
        //std::cout << foundReverse <<std::endl; 
    }
    std::cout<<"aufgabe 2: "<< occurances <<std::endl; 
    return 0; 
}