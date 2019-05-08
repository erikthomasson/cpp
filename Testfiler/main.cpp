#include <fstream>
#include <string>
#include <iostream>
#include </home/erik/c++/cpp/Laboration_1_Studentfiler/Includes/PriorityQueue.h>
#include <vector>
#include <map>

struct Node{
    std::map<Node*,unsigned int> adj;
};


int main(int argc , char* path[]){
    //path[1] == sökvägen till existerande fil
    //path[2] == billigaste rutten från A - B
    std::string str = "path";
    std::ifstream inFile;
    std::ofstream outFile; 
    std::map<std::string,Node*> nodes;
    
    inFile.open(str);
    if(inFile.is_open()){
        std::string val,val2,val3;
        std::getline(inFile,val,'\n');
        if(val == "DIRECTED"){
            std::getline(inFile, val, '\n');
            while(val != ""){
                //Node* newNode = new Node;
                nodes[val] = new Node;
                std::getline(inFile, val, '\n');
            }
            while(inFile.good()){
                std::getline(inFile, val, '\t');
                //från nod
                std::getline(inFile, val2, '\t');
                //till nod
                std::getline(inFile, val3, '\t');
                //vikt
                nodes[val]->adj[nodes[val2]] = std::stoi(val3);
            }
        
        }
        else if(val== "UNDIRECTED"){

        }
    }


}
