#include <fstream>
#include <string>
#include <iostream>
#include "PriorityQ.hpp"
#include <vector>
#include <map>
#include <limits.h>

struct Vertex{

    std::map<Vertex*,int> adj;
    int distance;
    Vertex* path;
    std::string name;
    bool operator<(Vertex& s){
        if(this->distance<s.distance) return true;
        else {return false;}
    }
};

void printPath(const Vertex& v, std::string& shortestPath){
    if(v.path != nullptr){
        printPath(*v.path, shortestPath);
    }
    
    shortestPath= shortestPath + v.name + " -> ";
    
}
void dijkstra(std::map<std::string,Vertex>& allVertex, std::string& startV){
    PriorityQueue<Vertex> q;
    allVertex[startV].distance=0;
    std::cout<<"hej1"<<std::endl;
    
    for(auto it = allVertex.begin();it != allVertex.end(); it++){
        q.enqueue(it->second);
    }
    std::cout<<"hej2"<<std::endl;
    Vertex* vertexP;
    while(!q.isEmpty()){
        vertexP= &q.peek();
        q.dequeue();
        
        std::cout<<"hej3"<<std::endl;
        for ( auto it = vertexP->adj.begin(); it != vertexP->adj.end(); it++ ){
            std::cout<<vertexP->distance<<std::endl;
            std::cout<<it->second<<std::endl;
            int dist = vertexP->distance + it->second;
            //std::cout<<it->second<<std::endl;
            std::cout<<it->first->distance<<std::endl;
            if(dist < it->first->distance && dist >= 0){
                if(it->first->name== "Second Town"){
                    std::cout<<"hej4"<<std::endl;
                    std::cout<<vertexP->name<<std::endl;
                }
                it->first->distance=dist;
                
                it->first->path=&allVertex[vertexP->name];
                q.enqueue(*it->first);
            }
        }

    }
    for(auto it = allVertex.begin();it != allVertex.end(); it++){
        std::cout<<it->first<< "="<<it->second.distance<<std::endl;
    }
}


std::map<std::string, Vertex> readFile(std::string path2File){
    std::ifstream inFile;
    std::map<std::string,Vertex> allVertex;
    inFile.open(path2File);

    if(inFile.is_open()){
        bool a=false;
        std::string val,val2,val3;
        std::getline(inFile,val);
        if(val == "DIRECTED\r"){
            while(!inFile.eof()){
                std::getline(inFile, val, '\r');
                std::getline(inFile, val2);
                std::cout<<val;
                if(val == "A\tJ\t3") std::cout<<"true"<<std::endl;
                if(val == ""){
                    a = true;
                    std::cout<<"jaha"<<std::endl;
                }
                else if(a == false){
                    std::cout<<"1"<<std::endl;
                    //if(val.size()>2) val = val.substr(0,val.size()-1);
                    Vertex newVertex;
                    newVertex.distance = INT_MAX;
                    newVertex.path = nullptr;
                    newVertex.name = val;
                    allVertex[val] = newVertex; 
                }
                else{
                    std::cout<<"2"<<std::endl;
                    std::string arr[3];
                    int count=0;
                    for(int i=0; i < val.size();i++){
                        std::cout<<count<<std::endl;
                        if(val[i]== '\t'){
                            count++;
                        }
                        else if(count == 0){
                            arr[0] += val[i];
                        }
                        else if(count == 1){
                            arr[1] += val[i];
                        }
                        else{
                            arr[2] += val[i];
                        }
                    }
                    std::cout<<arr[0]<<std::endl;
                    Vertex* vertexP;
                    vertexP=&allVertex[arr[1]];
                    allVertex[arr[0]].adj[vertexP] = std::stoi(arr[2]);
                    
                }
            }
        }
        else if( val == "UNDIRECTED\r"){
                while(!inFile.eof()){
                    std::getline(inFile, val, '\r');
                    std::getline(inFile, val2);
                    std::cout<<val;
                    if(val == ""){
                        a = true;
                        std::cout<<"jaha"<<std::endl;
                    }
                    else if(a == false){
                        std::cout<<"1"<<std::endl;
                        //if(val.size()>2) val = val.substr(0,val.size()-1);
                        Vertex newVertex;
                        newVertex.distance = INT_MAX;
                        newVertex.path = nullptr;
                        newVertex.name = val;
                        allVertex[val] = newVertex; 
                    }
                    else{
                        std::cout<<"2"<<std::endl;
                        std::string arr[3];
                        int count=0;
                        for(int i=0; i < val.size();i++){
                            std::cout<<count<<std::endl;
                            if(val[i]== '\t'){
                                count++;
                            }
                            else if(count == 0){
                                arr[0] += val[i];
                            }
                            else if(count == 1){
                                arr[1] += val[i];
                            }
                            else{
                                arr[2] += val[i];
                            }
                        }
                        std::cout<<arr[0]<<std::endl;
                        Vertex* vertexP;
                        Vertex* vertexP2;

                        vertexP = &allVertex[arr[1]];
                        vertexP2 = &allVertex[arr[0]];

                        allVertex[arr[0]].adj[vertexP] = std::stoi(arr[2]);
                        allVertex[arr[1]].adj[vertexP2] = std::stoi(arr[2]);
                    }
                }

        }else{
            std::cout<<"Unvalid File"<<std::endl;
            throw "Unvalid File";
        }
        /*
        std::getline(inFile,val,'\n');
        if(val.size() == 0) std::cout<<"true"<<std::endl;
        if(val != "DIRECTED")std::cout<<val<<std::endl;
        if(val == "DIRECTED\r"){
            std::getline(inFile, val);
            while(val[0] != '\r'){
                std::cout<<val;
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                if (val.size()!=2) val = val.substr(0,val.size()-1);
                else val = " " + val[0];
                newVertex.name = val;
                allVertex[val] = newVertex;
                std::getline(inFile, val);
            }
            std::cout<<"yes"<<std::endl;
            while(!inFile.eof()){
                std::getline(inFile, val, '\t');
                //från nod
                if(val.size()==1) val= " " + val[0]; 
                std::getline(inFile, val2, '\t');
                //till nod
                if(val2.size()==1) val2= " " + val2[0];
                std::getline(inFile, val3, '\n');
                //if(val2.size()==1) 
                val3 = val3.substr(0,val3.size()-1);
                //vikt
                std::cout<<val<<','<<val2<<','<<val3<<',';
                Vertex* vertexP;
                vertexP=&allVertex[val2];
                allVertex[val].adj[vertexP] = std::stoi(val3);
                
            }
            for(auto it = allVertex.begin();it != allVertex.end(); it++){
               std::cout<<it->first;
            }
        }
        else if(val=="UNDIRECTED\r"){
            std::getline(inFile, val, '\n');
            while(val[0] != '\r'){
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                if (val.size()!=2) val = val.substr(0,val.size()-1);
                newVertex.name=val;
                allVertex[val] = newVertex;
                std::getline(inFile, val, '\n');
            }
            std::cout<<"yes"<<std::endl;
            while(!inFile.eof()){
                std::getline(inFile, val, '\t');
                //från nod
                std::getline(inFile, val2, '\t');
                //till nod
                std::getline(inFile, val3, '\n');
                //vikt
                
                //Vertex A(val) ---weight(val3)---> Vertex B(val2)
                Vertex* vertexP;
                vertexP = &allVertex[val2];
                allVertex[val].adj[vertexP] = std::stoi(val3);
                

                //Vertex B(val2) ---weight(val3)---> Vertex A(val)
                Vertex* vertexP2;
                vertexP2= &allVertex[val];
                allVertex[val2].adj[vertexP2] = std::stoi(val3);
                
            }
        }
        else{
            std::cout<<"Unvalid File"<<std::endl;
            throw "Unvalid File";
        }*/
        return allVertex;
    
    }
    else{
        std::cout<<"Wrong file path or the file doesnt exist"<<std::endl;
        throw "Wrong file path or the file doesnt exist";
    }
}
void write2File(const std::map<std::string, Vertex>& allVertex, const int& distance, const std::string& shortestPath){
    std::ofstream outFile;
    outFile.open("Answer.txt");
    outFile<<"0"<<"\n";
    outFile<<"Distance from start to end: ";
    outFile<<distance<<"\n";
    outFile<<"All the stations on the way: ";
    outFile<<shortestPath.substr(0,shortestPath.size()-4);

}


int main(int argc , char* path[]){
    //path[1] == sökvägen till existerande fil
    //"First Town-Second Town" == billigaste rutten från A - B
    std::cout<< path[1]<<std::endl;
    std::cout<<path[2]<<std::endl;
    std::string start2end= path[2];
    std::cout<<"hej"<<std::endl;
    std::string startV,endV, filepath = path[1];
    bool startVOrEndV=false;
    for(int i=0;i<start2end.size();i++){
        if(path[2][i]=='-'){
            startVOrEndV = true;
            continue;
        }
        if(!startVOrEndV) startV+=start2end[i];
        else endV+=start2end[i];
    }
    std::cout<<"hej"<<std::endl;
    std::string shortestPath;
    std::ifstream inFile;
    std::ofstream outFile;
    std::map<std::string,Vertex> allVertex;
    
    allVertex=readFile(filepath.c_str());
    std::cout<<"readFile done"<<std::endl;
    for(auto it = allVertex.begin();it != allVertex.end(); it++){
        std::cout<<it->first<< "=="<<it->second.distance<<std::endl;
    }
    dijkstra(allVertex,startV);
    std::cout<<"dijkstra done"<<std::endl;
    printPath(allVertex[endV],shortestPath);
    std::cout<<"printpath done"<<std::endl;
    write2File(allVertex,allVertex[endV].distance,shortestPath);

/*
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
*/

}