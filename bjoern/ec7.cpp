#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> calcNext(const std::vector<std::string>& rules, int turns=10);
int count(const std::vector<int>& values);
std::string sort(const std::vector<std::pair<std::string, std::vector<std::string>>>& plans);
void quickSort(std::vector<std::pair<std::string, int>>& input, int low, int high);
int partition(std::vector<std::pair<std::string,int>>& input, int low, int high);


namespace std{
    ostream& operator<<(ostream& os, const std::vector<std::string>& v){
        for(const std::string& str: v){
            os << str << ", ";
        }
        return os; 
    }

    ostream& operator<<(ostream& os, const std::pair<std::string, std::vector<std::string>>& v){
        os << v.first << ": " << v.second;
        return os; 
    }

    ostream& operator<<(ostream& os, const std::vector<int>& v){
        for(int i:v){
            os << i <<", ";
        }
        return os; 
    }
}

int main(){
    std::vector<std::pair<std::string, std::vector<std::string>>> plans;

    std::string line;
    std::fstream file("everybody_codes_e2024_q07_p1.txt");
    if(!file.is_open()){
        std::cerr<< "file not found \n";
        return 1; 
    }
    while(std::getline(file, line)){
        size_t sep= line.find(':');
        std::string name=line.substr(0, sep);
        std::vector<std::string> rules; 
        std::string sub=line.substr(sep+1);
        while(sep!=std::string::npos){
            sep=sub.find(',');
            rules.push_back(sub.substr(0,sep));
            sub= sub.substr(sep+1); 
        }
        plans.push_back(std::make_pair(name, rules));
    }

    /*
    for(const auto& p: plans){
        std::cout << p << std::endl; 
    }
    */
    std::cout << sort(plans) <<std::endl; 
   

    return 0; 
}

std::string sort(const std::vector<std::pair<std::string, std::vector<std::string>>>& plans){
    std::vector<std::pair<std::string, int>> erg; 
    for(int i=0; i< plans.size(); i++){
        erg.push_back(std::make_pair(plans[i].first, count(calcNext(plans[i].second))));
    }
    quickSort(erg, 0, erg.size()); 

    std::string out="";
    for(const auto l: erg){
        out.append(l.first);
    }
    return out; 
}

//muss ja von groß nach klein
void quickSort(std::vector<std::pair<std::string, int>>& input, int low, int high){
    if(low<high){
        int middle= partition(input, low, high);
        quickSort(input, low, middle-1);
        quickSort(input, middle+1, high);
    }
}

int partition(std::vector<std::pair<std::string, int>>& input, int low, int high) {
    int pivot = input[low].second; 
    int pos = low; 

    for (int i = low + 1; i <= high; i++) { 
        if (input[i].second > pivot) { 
            pos++;
            std::swap(input[i], input[pos]);
        }
    }
    std::swap(input[low], input[pos]); 
    return pos; 
}

int count(const std::vector<int>& values){
    int erg=0; 
    for (int i=1; i<values.size(); i++){
        erg+=values[i];
    }
    return erg; 
}

std::vector<int> calcNext(const std::vector<std::string>& rules, int turns){
    std::vector<int> steps;
    steps.push_back(10);
    for(int i=0; i< turns; i++){
        int prev=steps[i];
        std::string rule= rules[i];
        if(rule=="="){
            steps.push_back(prev);
        } else if( rule=="+"){
            steps.push_back(++prev);
        } else if( rule=="-"){
            if(prev==0){
                steps.push_back(prev);
            } else{
                steps.push_back(--prev);
            }
        } else{
            std::cerr <<"illegal char met: "<< rule<< std::endl; 
        }
    }
    return steps; 
}