//Shortest path from a node to another node
#include "PriorityQ.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <limits.h>

struct Vertex
{

    std::map<Vertex *, int> adjacent;
    int distance;
    Vertex *path;
    std::string name;

    bool operator<(Vertex &s)
    {
        if (this->distance < s.distance)
            return true;
        else
        {
            return false;
        }
    }
};

void printPath(const Vertex &v, std::string &shortestPath)
{
    //take a Vertex and a string reference. When the function is done the text string which was in the argument list will change to the distance of the path from start Vertex to the end Vertex
    if (v.path != nullptr)
    {
        printPath(*v.path, shortestPath);
    }

    shortestPath += v.name + " -> ";
}
void dijkstra(std::map<std::string, Vertex> &allVertex, std::string &startV)
{
    std::cout<<startV;
    //Set the closest distance from start Vector to any other Vector
    std::pair<int, std::string> par;
    PriorityQueue<std::pair<int, std::string>> q;
    allVertex[startV].distance = 0;
    
    for (auto it = allVertex.begin(); it != allVertex.end(); it++)
    {
        std::cout<<it->first<<it->second.distance<<std::endl;
        par.first = it->second.distance;
        par.second = it->first;
        q.enqueue(par);
    }

    Vertex *vertexP;
    std::cout<<"hej"<<std::endl;
    while (!q.isEmpty())
    {
        par = q.peek();
        q.dequeue();
        std::cout<<par.first<< par.second<<std::endl;
        /*for (auto it = vertexP->adjacent.begin(); it != vertexP->adjacent.end(); it++){
            std::cout<<it->first->name<< " ";
        }
        */
        for (auto it = allVertex[par.second].adjacent.begin(); it != allVertex[par.second].adjacent.end(); it++)
        {
            std::cout<<it->first->name<< " "<< par.first + it->second <<" "<< allVertex[it->first->name].distance<<std::endl; //C 3 213123414325
            int dist = par.first + it->second;
            //std::cout<<dist <<" "<< allVertex[it->first->name].distance <<std::endl;
            if (allVertex[it->first->name].distance > dist && dist >=0) 
            {
                std::cout<<"bra"<<std::endl;
                allVertex[it->first->name].distance = dist;
                
                it->first->path = &allVertex[par.second];
                
                
                //std::cout<<par.first<<par.second<<std::endl;
                q.enqueue(make_pair(allVertex[it->first->name].distance, it->first->name ));
                
            }
        }
        std::cout<<"done"<<"\n"<<std::endl;
    }
}

std::map<std::string, Vertex> readFile(std::string path2File)
{
    //reads the file that is given in the argument list from running the program
    std::cout<<"readfile"<<std::endl;

    std::ifstream inFile;
    std::map<std::string, Vertex> allVertex;
    
    inFile.open(path2File);
    std::cout<<path2File<<std::endl;
    
    if (inFile.is_open())
    {
        std::cout<<"tjo"<<std::endl;
        bool isDirected, aVertexLine = true;
        std::string val, val2, val3;
        std::getline(inFile, val);
        std::cout<<val<<std::endl;
        if (val == "DIRECTED"){
            std::cout<<"sant"<<std::endl;
            isDirected = true;
        }
        else
            isDirected = false;

        while (!inFile.eof())
        {
            std::getline(inFile, val);
            
            std::cout<< val << std::endl;
            if (val == "")
            {
                std::cout<< "okej" << std::endl;
                aVertexLine = false;
            }
            else if (aVertexLine == true)
            {
                std::cout<< "okej2" << std::endl;   
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                newVertex.name = val;
                allVertex[val] = newVertex;
            }
            else
            {
                std::cout<< "okej3" << std::endl;
                if(val == "A\tJ\t3") std::cout<<"readfile"<<std::endl;
                std::string arr[3];
                int count = 0;
                for (unsigned int i = 0; i < val.size(); i++)
                {

                    if (val[i] == '\t')
                    {
                        count++;
                    }
                    else if (count == 0)
                    {
                        arr[0] += val[i];
                    }
                    else if (count == 1)
                    {
                        arr[1] += val[i];
                    }
                    else
                    {
                        arr[2] += val[i];
                    }
                }
                std::cout<< arr[0] << "_"<<arr[1] <<"_"<<arr[2] << std::endl;
                Vertex *vertexP;
                vertexP = &allVertex[arr[1]];
                allVertex[arr[0]].adjacent[vertexP] = std::stoi(arr[2]);
                if (!isDirected)
                {
                    vertexP = &allVertex[arr[0]];
                    allVertex[arr[1]].adjacent[vertexP] = std::stoi(arr[2]);
                }
            }
            
        }
        return allVertex;
    }
    else
    {
        throw "Wrong file path or the file doesnt exist";
    }
}
void write2File(const int &distance, const std::string &shortestPath)
{
    //Writes the distance from start node to end node and also writes which nodes that is on the way to an text file
    std::ofstream outFile;
    outFile.open("../Answer.txt");
    outFile << "0"
            << "\n";
    outFile << "Distance from start to end: ";
    outFile << distance << "\n";
    outFile << "All the stations on the way: ";
    outFile << shortestPath.substr(0, shortestPath.size() - 4);
}

int main( int argc, char *path[])
{
    std::cout <<"Entered file: " << "path[1]" << std::endl;
    std::cout <<"[Start station]-[End station]: " << "path[2]" << std::endl;
    std::cout <<"Output file: ./Answer.txt" << std::endl;

    std::string start2end = "a-i";
    std::string startV, endV, filepath = "../Tester implementationsval 1/Nodes9.txt";
    bool startVOrEndV = false;
    for (unsigned int i = 0; i < start2end.size(); i++)
    {
        if (start2end[i] == '-')
        {
            startVOrEndV = true;
            continue;
        }
        if (!startVOrEndV)
            startV += start2end[i];
        else
            endV += start2end[i];
    }
    std::string shortestPath;
    std::ifstream inFile;
    std::ofstream outFile;
    std::map<std::string, Vertex> allVertex;
    std::cout<< startV<< endV;
    allVertex = readFile(filepath.c_str());
    
    for( auto it = allVertex.begin(); it != allVertex.end(); it++){
        std::cout<<it->first<< allVertex[it->first].distance << " ";
        for (auto iter = allVertex[it->first].adjacent.begin(); iter != allVertex[it->first].adjacent.end(); iter++){
            std::cout<< iter->first->name<< iter->second <<" ";
        }
        std::cout<<std::endl;
    }
    
    std::cout<<"yoo"<<std::endl;
    dijkstra(allVertex, startV);
    for( auto it = allVertex.begin(); it != allVertex.end(); it++){
        std::cout<<it->first<< allVertex[it->first].distance << " ";
        for (auto iter = allVertex[it->first].adjacent.begin(); iter != allVertex[it->first].adjacent.end(); iter++){
            std::cout<< iter->first->name<< iter->second <<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"sup"<<std::endl;
    std::cout<<shortestPath<<std::endl;
    printPath(allVertex[endV], shortestPath);
    std::cout<<shortestPath<<std::endl;
    write2File(allVertex[endV].distance, shortestPath);
}