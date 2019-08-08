#include <iostream>
#include <string>
#include <fstream>

int calcfile(std::string inputFile);
int main()
{
    std::cout<<calcfile("text.txt")<<std::endl;

    return 1;
}

int calcfile(std::string inputFile)
{
    std::ifstream file(inputFile);
    int sum = 0;

    if(file.is_open())
    {
        while(file.good())
        {
            std::string num;
            std::getline(file,num,'\n');
            sum += std::stof(num);


        }
    }
return sum;
}