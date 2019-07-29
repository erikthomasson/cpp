//Shortest path from a node to another node
#include <fstream>
#include <string>
#include <iostream>
#include "PriorityQ.hpp"
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
    //take a Vertex and a string reference. When the function is done the text string was in the argument list has changed to the path from start Vertex to the end Vertex
    if (v.path != nullptr)
    {
        printPath(*v.path, shortestPath);
    }

    shortestPath += v.name + " -> ";
}
void dijkstra(std::map<std::string, Vertex> &allVertex, std::string &startV)
{
    //set the closest distance from start Vector to any other Vector
    PriorityQueue<Vertex> q;
    allVertex[startV].distance = 0;

    for (auto it = allVertex.begin(); it != allVertex.end(); it++)
    {
        q.enqueue(it->second);
    }
    Vertex *vertexP;
    while (!q.isEmpty())
    {
        vertexP = &q.peek();
        q.dequeue();

        for (auto it = vertexP->adjacent.begin(); it != vertexP->adjacent.end(); it++)
        {
            int dist = vertexP->distance + it->second;

            if (dist < it->first->distance && dist >= 0)
            {
                it->first->distance = dist;

                it->first->path = &allVertex[vertexP->name];
                q.enqueue(*it->first);
            }
        }
    }
}

std::map<std::string, Vertex> readFile(std::string path2File)
{
    //reads the file that is given in the argument list from running the program
    std::ifstream inFile;
    std::map<std::string, Vertex> allVertex;
    inFile.open(path2File);

    if (inFile.is_open())
    {
        bool isDirected, aVertexLine = true;
        std::string val, val2, val3;
        std::getline(inFile, val);
        if (val == "DIRECTED\r")
            isDirected = true;
        else
            isDirected = false;

        while (!inFile.eof())
        {
            std::getline(inFile, val, '\r');
            std::getline(inFile, val2);
            if (val == "")
            {
                aVertexLine = false;
            }
            else if (aVertexLine == true)
            {
                Vertex newVertex;
                newVertex.distance = INT_MAX;
                newVertex.path = nullptr;
                newVertex.name = val;
                allVertex[val] = newVertex;
            }
            else
            {

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
                Vertex *vertexP;
                vertexP = &allVertex[arr[1]];
                allVertex[arr[0]].adjacent[vertexP] = std::stoi(arr[2]);
                if (isDirected)
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
    outFile.open("Answer.txt");
    outFile << "0"
            << "\n";
    outFile << "Distance from start to end: ";
    outFile << distance << "\n";
    outFile << "All the stations on the way: ";
    outFile << shortestPath.substr(0, shortestPath.size() - 4);
}

int main( int argc, char *path[])
{
    std::cout <<"Input file: " << path[1] << std::endl;
    std::cout <<"[Start station]-[End station]: " << path[2] << std::endl;
    std::cout <<"Output file: ./Answer.txt" << std::endl;

    std::string start2end = path[2];
    std::string startV, endV, filepath = path[1];
    bool startVOrEndV = false;
    for (unsigned int i = 0; i < start2end.size(); i++)
    {
        if (path[2][i] == '-')
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

    allVertex = readFile(filepath.c_str());
    dijkstra(allVertex, startV);
    printPath(allVertex[endV], shortestPath);
    write2File(allVertex[endV].distance, shortestPath);
}