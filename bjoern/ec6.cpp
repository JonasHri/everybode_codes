#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

struct Node{
    std::string name;
    std::list<Node> children; 
    

    Node(std::string n): name(n)
    {
    }
    Node(){}

    void append(Node n){
        this->children.push_back(n);
    }

    friend std::ostream& operator<<(std::ostream& os, const Node n){
        os << n.name;
        return os; 
    }

    bool operator==(const Node& other) const{
        return (name== other.name);
    }
};

template<>
struct std::hash<Node>
{
    std::size_t operator()(const Node& s) const noexcept
    {
        std::size_t h = std::hash<std::string>{}(s.name);
        return h;
    }
};
 

int main(){

    std::unordered_map<std::string, Node> input; 

    Node root; 

    std::string line;
    std::fstream file("everybody_codes_e2024_q06_p1.txt");
    if(!file.is_open()){
        std::cerr <<"file not foiund"<<std::endl;
    }
    while(std::getline(file, line)){
        size_t sepCol = line.find(':');
        if(sepCol!= std::string::npos){
            //std::cout << "Der doppelpunkt ist an stelle: "<<sepCol<<std::endl;
            //std::cout << "der string lautet: \""<< line<<"\"" <<std::endl; 
            std::string father= line.substr(0, sepCol);
            Node fatherNode(father);
            std::string tmp= line.substr(sepCol+1);
            size_t sepKom = tmp.find(',');
            while(sepKom != std::string::npos){
                //std::cout << tmp<< std::endl;
                Node nxt = tmp.substr(0, sepKom);
                //std::cout << "Die neue Node ist: "<< nxt <<std::endl;
                fatherNode.append(nxt); 
                tmp=tmp.substr(sepKom+1);
                sepCol=sepKom+1;
                sepKom = tmp.find(',');    
            }
            Node lst (tmp);
            //std::cout <<"last: "<< lst << std::endl; 
            fatherNode.append(lst);
            input.push_back(fatherNode);
            if(father=="RR"){
                root= fatherNode;
            }
            //std::cout << father << " : "<< fatherNode <<std::endl; 
        }
        else{
            std::cerr<< "couldn´t parse line"<< line <<std::endl; 
        }
    }
    //build the tree:

    Node curr= root;
    std::cout << "curr: " << curr << std::endl; 
    for(Node child: curr.children){
        std::cout << child<< std::endl;
        child = input.find(child); 

    }
    




    return 0; 
}