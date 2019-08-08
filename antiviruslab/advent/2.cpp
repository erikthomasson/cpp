#include <iostream>
#include <string>
#include <fstream>
#include <map>



int main() 
{
    int two=0, three=0, ja=0, jaja=0;
    std::ifstream file("text1.txt");
    if(file.is_open())
    {
        while(file.good())
        {
            std::map<char, int> lettercount;
            std::string value;
            std::getline(file, value);
            for (int i = 0; i<value.size();i++)
            ++lettercount[value[i]];
            for(auto it = lettercount.begin(); it != lettercount.end(); it++)
            {
                
                if(it->second == 2) 
                {
                    std::cout<<it->second<<std::endl;
                    two++;
                }
                if(it->second == 3)
                {
                    std::cout<<it->second<<std::endl;
                    three++;
                }

            }
            if(two > 0) ja++;
            if(three > 0) jaja++;
            two = 0;
            three = 0;
        





        }
    
    }
    std::cout<< two<<std::endl;
    std::cout<< three<<std::endl;
    std::cout<< ja * jaja;
}