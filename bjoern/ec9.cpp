#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <limits>


int numDots(int brigthnes);
void setupMins();

int main(){
    std::vector<int> sparkballs;

    std::string line;
    std::fstream file("everybody_codes_e2024_q09_p3.txt");
    if(!file.is_open()){
        std::cerr <<"file not found"<<std::endl;
    }
    while(std::getline(file, line)){
        sparkballs.push_back(std::stoi(line));
    }
    setupMins(); 

    std::vector<int> test={156488,352486,546212};
    int erg=0;
    // erg=numDots(test[0]); 
    for(int ball: sparkballs){
        int fewest= std::numeric_limits<int>::max();
        for(int i=0; i<=50-ball%2 ; i++){
            int tmp1=numDots(ball/2 -i);
            int tmp2=numDots( ball/2 +i+ ball%2);
            int calcedDots = tmp1 + tmp2;
            if(calcedDots<fewest){
                fewest= calcedDots;
                std::cout <<"fewest: "<< fewest<<" left: "<< tmp1 << " right " <<tmp2 << std::endl;  
            }
        }
        std::cout <<"fewest: "<< fewest<<std::endl; 
        erg += fewest; 
    }
    // for(int ball: sparkballs){
    //     std::cout <<"starting with "<<ball <<std::endl; 
    //     int tmp= numDots(ball);
    //     erg += tmp;
    //     std::cout <<"erg: "<< tmp<<std::endl; 
    // }
    std::cout << erg << std::endl; 

    return 0; 
}

std::unordered_map<int,int> mins;
std::vector<int> coins ={1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101};

// 1, 3, 5, 10, 15, 16, 20, 24, 25, 30
void setupMins(){
    for(const int& coin: coins){
        mins.insert({coin, 1});
    }
    std::reverse(coins.begin(), coins.end());
}

int numDots(int brigthnes){
    // std::cout << brigthnes <<std::endl; 
    if( brigthnes <-1){
        return -10; 
    }
    if(mins.contains(brigthnes)){
        return mins.at(brigthnes);
    }
    int erg;
    int min= std::numeric_limits<int>::max(); 
    int tmp; 
    for(const int& coin: coins){
        // std::cout << brigthnes<<" - " << coin << std::endl; 
        if((tmp=numDots(brigthnes-coin))<min){
            if(tmp <1){
                continue;
            }
            // std::cout <<"tmp: "<< tmp <<std::endl; 
            min= tmp+1;
        }
    }
    erg=min;
    mins.insert({brigthnes, erg}); 
    return erg; 

    //Der sucht jetzt nicht die optimale Kombi, sondern nimmt das Größte... müssen wir mal gucken... 
     
    if(brigthnes>10){
        brigthnes-=10;
    }else if(brigthnes>5){
        brigthnes -=5;
    }else if(brigthnes>3){
        brigthnes -=3;
    }else{
        brigthnes--;
    }
    std::cout << brigthnes << std::endl;
    return 1+ numDots(brigthnes);
}

