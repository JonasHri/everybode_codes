#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <chrono>

int countSymbol(const std::string& currWheel);
std::string calcWheel(const std::vector<std::vector<std::string>>& wheels, const std::vector<int>& turns, std::vector<int>& currPos);
void resizeVector(std::vector<std::string>& v);
int countSymbolpart2(const std::string& currWheel);

int main(){
    std::vector<int> turns; 
    std::vector<std::vector<std::string>> wheels;

    std::string line;
    std::fstream file("everybody_codes_e2024_q16_p2_TEST.txt");
    std::getline(file, line);
    std::stringstream ss;
    ss << line;
    int a; 
    while(ss>>a){
        turns.push_back(a);
        if(ss.peek()==','){
            ss.ignore(); 
        }
    }
    wheels.reserve(turns.size()); 
    
    while(std::getline(file, line)){
        ss <<line; 
        std::string cat;
        int count=0; 
        for(int i=0; i<line.length(); i+=4){
            cat=line.substr(i, 3);
            // std::cerr << cat << std::endl; 
            wheels[count].push_back(cat);
            count++; 
        }
    }

    // std::cout<< wheels[1][2]<<std::endl; 
    // std::cout << countSymbol(" -_- -.- ^_^") <<std::endl; 
    std::string currWheel; 
    std::vector<int> currPos;
    for(int i=0; i< turns.size(); i++){
        currPos.push_back(0); 
        resizeVector(wheels[i]); 
        // currWheel+= wheels[i][0];
        // currWheel+= " ";
    }
    // std::cout << "currpos size: "<<currPos.size() << " turns size: "<<turns.size() <<std::endl; 
    long erg=0; 
    long erg2=0; 
    // std::string igel, hase;
    // igel= currWheel;
    auto startTimer= std::chrono::high_resolution_clock::now();
    long turnlenght=1000;  // Anzahl iterationen
    long remainingTurns = turnlenght;
    bool shortCutTaken=false; 
    for(long i=0; i<turnlenght; i++){
        currWheel= calcWheel(wheels, turns, currPos); // Ein String, der die aktuellen Gesichter hat, z.B. >.- -.- >.<
        erg += countSymbolpart2(currWheel); //addiert die anzhal der passenden Augen
        int currPosSum=0; 
        for(int p: currPos){ //Wenn alle arraypositionen 0 sind, dann gibts einen zyklus
            currPosSum += p; 
        }
        if(currPosSum==0 && !shortCutTaken){
            long numCycles= turnlenght / i; 
            // std::cout << "cyclelen: "<< i <<" with: "<< erg << " and numCycles " << numCycles<<std::endl;
            erg2= erg;
            erg2 *= numCycles;
            remainingTurns= i * numCycles;
            // std::cout << "next i is: "<<remainingTurns <<std::endl; 
            std::cout<< "erg2 in shortcut: "<<erg2 << " comapred with erg: "<< erg <<". with turns completed : "<<remainingTurns<<". Dabei gibt es:"<< numCycles<<" Zyklen. Das macht: erg*numCycles "<< erg*numCycles<<std::endl;
            // break;
            shortCutTaken= true; 
        }
        if(i==944){
            std::cout <<i <<": " << "erg: "<<erg <<" erg2: "<<erg2 <<" zusatz: " <<  countSymbolpart2(currWheel) << std::endl; 
        }
    }
    // std::cout <<"erg after quickstop: "<< erg << " and erg2 : " <<erg2<<"  diff= "<<erg-erg2 << std::endl; 
    // for(const int& i: currPos){
    //     std::cout << i <<", "; 
    // }
    for(int& i: currPos){
        i=0; 
    }
    // std::cout <<currWheel <<std::endl; 
    int cnt=1; 
    int additionals=0;
    // int additionals= countSymbolpart2(currWheel); 
    while(++remainingTurns<turnlenght){
        // std::cout << cnt++  <<" : ";
        currWheel= calcWheel(wheels, turns, currPos);
        int increase =  countSymbolpart2(currWheel);
        additionals += increase;
        // for(const int& i: currPos){
        //     std::cout << i <<", "; 
        // }
        // std::cout <<currWheel << "\t" << additionals<< " (+"<<increase<<")"<<std::endl; 

    }
    erg2+= additionals; 
    auto endTimer= std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer);
    std::cout << "The loop took: " << duration.count() << " ms" << std::endl; 
    // std::cout << currWheel <<std::endl; 
    // std::cout << countSymbolpart2(currWheel) <<std::endl; 
    std::cout << "erg2:" <<erg2 <<" erg: "<< erg<< std::endl;
    if(erg2==280014668134){
        std::cout << "jippie "<< std::endl; 
    }

    return 0; 
}

void resizeVector(std::vector<std::string>& v){
    int numEmptyStrings=0; 
    for(int i=0; i<v.size(); i++){
        if(v[i]!="   "){
            numEmptyStrings++;
            // std::cout << v[i] << std::endl; 
        }
        else{
            break;
        }
    }
    // std::cout << numEmptyStrings <<std::endl; 
    v.resize(numEmptyStrings); 
}

std::string calcWheel(const std::vector<std::vector<std::string>>& wheels, const std::vector<int>& turns, std::vector<int>& currPos){
    std::string erg;
    for(int i=0; i< currPos.size(); i++){
        currPos[i]+= turns[i];
        currPos[i] %= wheels[i].size();
        std::string tmp = wheels[i][currPos[i]]; 
        // std::cout << tmp <<std::endl; 
        erg += tmp;
        erg += " ";  
        // std::cout << currPos[i] << " @ "<< i<<" size: " << wheels[i].size() << std::endl; 
    }
    return erg; 
    
}

int countSymbolpart2(const std::string& currWheel){
    int erg=0;
    std::unordered_set<char> searched;
    for(int i=0; i< currWheel.length(); i+=2){
        const char& c= currWheel[i];
        int count=0;
        if(c==' '){
            continue;
        }
        if(searched.contains(c)){
            continue;
        }
        for(int j=i; j<currWheel.length(); j+=2){
            if(currWheel[j]==c){
                count++;
            }
        }
        if(count>=3){
            erg++;
            count-=3;
            while(count>0){
                erg++;
                count--;
            }
        }
        searched.insert(c);
    }
    return erg; 
}

int countSymbol(const std::string& currWheel){
    int erg=0;
    std::unordered_set<char> searched;
    for(const char& c: currWheel){
        if(c==' '){
            continue;
        }
        if(searched.contains(c)){
            continue;
        }
        auto count= std::ranges::count(currWheel, c);
        // std::cout << "char: "<<c <<" count: "<< count<<std::endl; 
        if(count>=3){
            erg++;
            count-=3;
            while(count>0){
                erg++;
                count--;
            }
        }
        searched.insert(c); 
    }
    return erg; 
}