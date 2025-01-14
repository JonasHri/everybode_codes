#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(){
    std::vector<std::string> words;
    std::string text;

    std::string line;
    std::fstream file("everybody_codes_e2024_q02_p1.txt");
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
            text=line;
        }
    }
    int occurances=0; 
    size_t pos; 
    int tmp; 
    for(const auto w:words){
        pos=0;
        while((tmp= text.find(w,pos))!= std::string::npos){
            //std::cout << tmp <<std::endl;
            occurances++;
            pos=tmp + w.length();
        }
    }
    std::cout<<"aufgabe 1. "<< occurances <<std::endl; 
    return 0; 
}