#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int quicksortMeanfinder(std::vector<int>& arr, int left, int right, int middleindex);
int partition(std::vector<int>& arr, int left, int right);
int findMedian(std::vector<int>& arr);


int main(){
    std::vector<int> nails;

    std::string line;
    std::fstream file("everybody_codes_e2024_q04_p3.txt");
    if(!file.is_open()){
        std::cerr << "file not found \n";
        return 1;
    }
    while(std::getline(file, line)){
        nails.push_back(std::stoi(line));
    }

    int median= findMedian(nails); 
    long hits=0; 
    for(int nail: nails){
        //std::cout << nail <<std::endl; 
        if(nail> median){
            hits+= nail - median;
        }else{
            hits+= median - nail; 
        } 
    }
    std::cout << hits <<std::endl;
    return 0; 
}

int quicksortMeanfinder(std::vector<int>& arr, int left, int right, int middleindex){
    if(left<=right){
        int middle= partition(arr, left, right);
        if(middle== middleindex){
            return arr[middle];
        }
        if(middle< middleindex){
            return quicksortMeanfinder(arr, middle+1, right, middleindex);
        }
        else{
            return quicksortMeanfinder(arr, left, middle, middleindex);
        }
    }
    return -1; 
}

int partition(std::vector<int>& arr, int left, int right){
    int pivot= arr[left]; 
    int pos= left;

    for(int i= left+1; i<=right; i++){
        if(arr[i]<=pivot){
            pos++;
            std::swap(arr[i], arr[pos]);
        }
    }
    std::swap(arr[left], arr[pos]);
    return pos; 
}

int findMedian(std::vector<int>& arr) {
    int n = arr.size();
    if (n % 2 == 1) {
        return quicksortMeanfinder(arr, 0, n - 1, n / 2);
    } else {
        int mid1 = quicksortMeanfinder(arr, 0, n - 1, n / 2 - 1);
        int mid2 = quicksortMeanfinder(arr, 0, n - 1, n / 2);
        return (mid1 + mid2) / 2;
    }
}