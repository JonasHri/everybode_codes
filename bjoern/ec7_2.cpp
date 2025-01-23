#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

std::string move(const std::string& map, const std::vector<std::pair<std::string, std::string>>& rules);
std::vector<std::pair<std::string, int>> mergesort(std::vector<std::pair<std::string, int>>& arr);
std::vector<std::pair<std::string, int>> merge(const std::vector<std::pair<std::string, int>>& left, const std::vector<std::pair<std::string, int>>& right);
int playerPath(const std::string& map, const std::string& rules);
int step(const char& rule);


int main(){
    std::vector<std::pair<std::string, std::string>> rules;

    std::string line;
    std::fstream file("everybody_codes_e2024_q07_p2.txt");
    if(!file.is_open()){
        std::cerr<< "file not found \n";
        return 1; 
    }
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ':');
        //std::cout << "name: " <<name << std::endl; 
        std::string rule; 
        std::string token;
        size_t pos=-1;
        while(ss>>token) {
            while ((pos=token.rfind(',')) != std::string::npos) {
                token.erase(pos, 1);
            }
            rule = token;   
        }
        rules.push_back(std::make_pair(name, rule));
        //std::cout << rule <<std::endl; 
    }

    //parse map:
    std::string map;
    std::stack<std::string> stack;
    std::fstream file2("everybody_codes_e2024_q07_p2_MAP.txt");
    if(!file2.is_open()){
        std::cerr<< "file not found \n";
        return 1; 
    }
    while(std::getline(file2, line)){
        std::stringstream ss(line);
        std::string token1, token2; 
        while(ss>>token1){
            if(ss>>token2){
                stack.push(token1);
                map.append(token2);
            } else{
                if(map.empty()){
                    map.append(token1);
                }
                else{
                    std::reverse(token1.begin(), token1.end()); 
                    map.append(token1); 
                }
            }
        }
    }
    while(!stack.empty()){
        map.append(stack.top());
        stack.pop(); 
    }

    std::string erg= move(map, rules); 
    std::cout<< erg << std::endl; 
    return 0; 
}

std::string move(const std::string& map, const std::vector<std::pair<std::string, std::string>>& rules){
    std::string order="";
    std::vector<std::pair<std::string, int>> power;
    power.reserve(rules.size());
    for(int i=0; i<rules.size(); i++){
        power.push_back(std::make_pair(rules[i].first, playerPath(map, rules[i].second)));
    }
    mergesort(power); 
    for(int i=0; i< power.size(); i++){
        order.append(power[i].first);
    }
    return order; 
}

std::vector<std::pair<std::string, int>> mergesort(std::vector<std::pair<std::string, int>>& arr){
    int n = arr.size();
    if(n<=1){
        return arr; 
    }
    int m= n/2; //mittelpunkt 
    std::vector<std::pair<std::string, int>> left;
    std::vector<std::pair<std::string, int>> right;
    for(int i=0; i<m; i++){
        left.push_back(arr[i]);
    }
    for(int i=m; i<n; i++){
        right.push_back(arr[i]);
    }
    return merge(mergesort(left), mergesort(right));
}

std::vector<std::pair<std::string, int>> merge(const std::vector<std::pair<std::string, int>>& left, const std::vector<std::pair<std::string, int>>& right){
    std::vector<std::pair<std::string, int>> erg;
    erg.reserve(left.size()+right.size());
    int pleft=0, pright=0;
    while (pleft < left.size() && pright < right.size()) {
        //std::cout << left[pleft].second <<std::endl;
        if (left[pleft].second >= right[pright].second) {
             
            erg.push_back(left[pleft++]);
        } else {
            erg.push_back(right[pright++]);
        }
    }
    while (pleft < left.size()) {
        erg.push_back(left[pleft++]);
    }
    while (pright < right.size()) {
        erg.push_back(right[pright++]);
    }
    return erg; 
}

int playerPath(const std::string& map, const std::string& rules) {
    int totalSteps = 0;
    int currentStep = 10;
    size_t mapLen = map.length();
    size_t rulesLen = rules.length();

    for (size_t i = 0; i < 10 * mapLen; i++) {
        int mapPos = i % mapLen;
        int rulePos = i % rulesLen;
        if (map[mapPos] == '=') {
            currentStep += step(rules[rulePos]);
        } else {
            currentStep += step(map[mapPos]);
        }
        totalSteps += currentStep;
    }
    return totalSteps;
}

int step(const char& rule){
    int res=0;
    if(rule=='-'){
        res=-1;
    } else if(rule=='+'){
        res=1;
    }
    return res; 
}