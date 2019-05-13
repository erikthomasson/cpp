#include <fstream>
#include <string>
#include <iostream>
#include "/home/erik/c++/cpp/Testfiler/PriorityQ.hpp"
#include <vector>
#include <map>
#include <limits.h>

struct Vertex{

    std::map<Vertex&,int> adj;
    int distance;
    Vertex* path;
    std::string name;
    int operator<(Vertex& s){
        if(this->distance<s.distance) return this->distance;
        else return s.distance;
    }
    int operator>(Vertex& s){
        if(this->distance>=s.distance) return this->distance;
        else return s.distance;
    }
};

void printPath(Vertex v, std::string& shortestPath){
    if(v.path!=nullptr){
        printPath(*v.path, shortestPath);
    }
    shortestPath+= (v.name + " -> ");
    
}
void dijkstra(std::map<std::string,Vertex>& allVertex){
    PriorityQueue<Vertex> q;
    allVertex["start vertex"].distance=0;
    
    for(auto it = allVertex.begin();it != allVertex.end(); it++){
        q.enqueue(it->second);
    }
    Vertex* vertexP = new Vertex;
    while(!q.isEmpty()){
        *vertexP= q.peek();
        q.dequeue();
        for ( auto it = vertexP->adj.begin(); it != vertexP->adj.end(); it++ ){
            int dist = vertexP->distance + it->second;
            if(dist < it->second){
                it->first.distance=dist;
                it->first.path=vertexP;
            }
        }
    }
    delete vertexP;
}


std::map<std::string, Vertex> readFile(std::string path2File){
    std::ifstream inFile;
    std::map<std::string,Vertex> allVertex;
    inFile.open(path2File);

    if(inFile.is_open()){
        std::string val,val2,val3;
        std::getline(inFile,val,'\n');
        if(val == "DIRECTED"){
            std::getline(inFile, val, '\n');
            while(val != ""){
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                allVertex[val] = newVertex;
                std::getline(inFile, val, '\n');
            }
            while(inFile.good()){
                std::getline(inFile, val, '\t');
                //från nod
                std::getline(inFile, val2, '\t');
                //till nod
                std::getline(inFile, val3, '\t');
                //vikt
                allVertex[val].name=val;
                allVertex[val].adj[allVertex[val2]] = std::stoi(val3);
                
            }
        }
        else if(val=="UNDIRECTED"){
            std::getline(inFile, val, '\n');
            while(val != ""){
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                allVertex[val] = newVertex;
                std::getline(inFile, val, '\n');
            }
            while(inFile.good()){
                std::getline(inFile, val, '\t');
                //från nod
                std::getline(inFile, val2, '\t');
                //till nod
                std::getline(inFile, val3, '\t');
                //vikt
                
                //Vertex A(val) ---weight(val3)---> Vertex B(val2)
                allVertex[val].name=val;
                allVertex[val].adj[allVertex[val2]] = std::stoi(val3);
                

                //Vertex B(val2) ---weight(val3)---> Vertex A(val)
                allVertex[val2].name=val;
                allVertex[val2].adj[allVertex[val]] = std::stoi(val3);
                
            }
        }
        else{
            throw "Unvalid File";
        }
        return allVertex;
    
    }
}
void write2File(const std::map<std::string, Vertex>& allVertex, const int& distance, const std::string& shortestPath){
    std::ofstream outFile;
    outFile.open("Answer.txt");
    outFile<<"0"<<"\n";
    outFile<<distance<<"\n";
    outFile<<shortestPath<<"\n";

}


int main(int argc , char* path[]){
    //path[1] == sökvägen till existerande fil
    //path[2] == billigaste rutten från A - B
    std::string str=path[2], startV,endV;
    bool diff=false;
    for(int i=0;i<str.size();i++){
        if(str[i]=='-') continue;
        if(!diff) startV+=str[i];
        else endV+=str[i];
    }
    std::string str = "path[1]";
    std::ifstream inFile;
    std::ofstream outFile; 
    std::map<std::string,Vertex> allVertex;
    
    inFile.open(str);
    if(inFile.is_open()){
        std::string val,val2,val3;
        std::getline(inFile,val,'\n');
        if(val == "DIRECTED"){
            std::getline(inFile, val, '\n');
            while(val != ""){
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                allVertex[val] = newVertex;
                std::getline(inFile, val, '\n');
            }
            while(inFile.good()){
                std::getline(inFile, val, '\t');
                //från nod
                std::getline(inFile, val2, '\t');
                //till nod
                std::getline(inFile, val3, '\t');
                //vikt
                allVertex[val].name=val;
                allVertex[val].adj[allVertex[val2]] = std::stoi(val3);
                
            }
            PriorityQueue<Vertex> q;
            allVertex[startV].distance=0;
            
            for(auto it = allVertex.begin();it != allVertex.end(); it++){
                q.enqueue(it->second);
            }
            Vertex* vertexP = new Vertex;
            while(!q.isEmpty()){
                *vertexP= q.peek();
                q.dequeue();
                for ( auto it = vertexP->adj.begin(); it != vertexP->adj.end(); it++ ){
                    int dist = vertexP->distance + it->second;
                    if(dist < it->second){
                        it->first.distance=dist;
                        it->first.path=vertexP;
                    }
                    }
                }
            delete vertexP;
            }
        else if(val== "UNDIRECTED"){
            std::getline(inFile, val, '\n');
            while(val != ""){
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                allVertex[val] = newVertex;
                std::getline(inFile, val, '\n');
            }
            while(inFile.good()){
                std::getline(inFile, val, '\t');
                //från nod
                std::getline(inFile, val2, '\t');
                //till nod
                std::getline(inFile, val3, '\t');
                //vikt
                
                //Vertex A(val) ---weight(val3)---> Vertex B(val2)
                allVertex[val].name=val;
                allVertex[val].adj[allVertex[val2]] = std::stoi(val3);
                
                //Vertex B(val2) ---weight(val3)---> Vertex A(val)
                allVertex[val2].name=val;
                allVertex[val2].adj[allVertex[val]] = std::stoi(val3);   
            }
        }
        else{
            throw "Unvalid File";
        }
    }
    else{
        throw "Wrong file path or the file doesnt exist";
    }
    std::string shortestPath;
    printPath(allVertex[endV], shortestPath);
    write2File(allVertex,allVertex[startV].distance,shortestPath);

}