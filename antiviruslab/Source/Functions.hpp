
//Erik Thomasson


#ifndef FUNCTIONS_HPP
#define FUNCTION_HPP
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h> 
#include <iostream>
#include <string.h>
#include <string>     
#include <cstdint>
#include <iomanip>    



std::string hextoascii(std::string&);

std::unordered_map<std::string, std::string> virusdatabasen();

bool felidentifiering(const std::string & virus, const std::string &checkfile );

void filtraversering(const char *dir_Name);

void checkthevirusdatabase();



#endif