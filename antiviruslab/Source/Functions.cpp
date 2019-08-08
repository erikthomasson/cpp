#include "Functions.hpp"
#include <iomanip>
#include <functional>

//Erik Thomasson

void checkthevirusdatabase(){
    // Check if the virus database with help of a hash-signature of the database
    std::ifstream hashfile("/home/erik/c++/antiviruslab/THEFILE.txt");
    std::ifstream vdb("/home/erik/c++/antiviruslab/signatures.db");

    std::size_t vdbhash;

    if (!vdb.is_open()){
        std::cout << "WARNING!\nThe virusdatabase has been deleted or moved" << std::endl;
    }
    else{
        std::string hash, value;
        while (vdb.good()){
            std::getline(vdb, value);
            hash += value;
        }
        vdbhash = std::hash<std::string>{}(hash);
    }

    if (!hashfile.is_open()){
        std::ofstream makef("/home/erik/c++/antiviruslab/THEFILE.txt");
        std::cout << "WARNING!\nEither this is the first time you run this program or the virusdatabase has been changed" << std::endl;
        makef << vdbhash;
        makef.close();
    }
    else{
        std::string hashvalue;

        while (hashfile.good()){
            std::getline(hashfile, hashvalue);
        }

        if (hashvalue == std::to_string(vdbhash)){
            std::cout << "The database has not been changed" << std::endl;
        }
        else{
            std::cout << "The virusdatabase has been changed" << std::endl;
        }
    }
    hashfile.close();
    vdb.close();
}

std::string hextoascii(std::string &hex){
    //Converts hexvalue to asciivalue
    std::string returnString;
    for (int i = 0; i < hex.length(); i += 2){
        std::string byte = hex.substr(i, 2);
        char chr = strtol(byte.c_str(), nullptr, 16);
        if ((chr != '\n') && (byte != "0d") && (chr != ' ') && (chr != '\t'))
            returnString.push_back(chr);
    }
    return returnString;
}

bool filidentifiering(const std::string &virus, const std::string &checkfile){
    //Compare asciivalue from virusdatabase(virus) with a file(checkfile)
    std::ifstream checkF;
    checkF.open(checkfile, std::ios::binary);
    //std::cout<<"new virus\n\n\n"<<std::endl;
    char x;
    int i = 0;
    while (checkF >> x){
        //if(i>10)
        //std::cout<<virus[i]<<"=="<<x<<std::endl;

        if (i >= virus.size())
            return true;

        if (x != virus[i]){
            i = -1;
        }
        i++;
        //else std::cout<<"något händer"<<std::endl;
    }

    return false;
}

void filtraversering(const char *dir_Name){
    //Finds all files under the map that is inserted as a argument in the function
    std::unordered_map<std::string, std::string> vsdmapp = virusdatabasen();
    DIR *dir;
    struct dirent *entry;
    struct stat info;

    dir = opendir(dir_Name);

    while ((entry = readdir(dir)) != nullptr){
        if(((entry->d_name[0] != '.') || (entry->d_name[1] != 0)) && ((entry->d_name[1] != '.') || (entry->d_name[0] != '.'))){
            std::string path = std::string(dir_Name) + '/' + std::string(entry->d_name);
            stat(path.c_str(), &info);
            if (S_ISDIR(info.st_mode)){
                //Mapp
                filtraversering((char *)path.c_str());
            }
            else{
                //File

                auto it = vsdmapp.begin();
                while (it != vsdmapp.end()){
                    std::ofstream file("dv1577.log.txt", std::ios::app);
                    if (filidentifiering(it->second, path)){
                        //The file has a virus
                        file << "Virusname: " << it->first
                             << "\nFilen: " << std::string(entry->d_name)
                             << "\nSökvägen till filen:" << path
                             << "\n-----------------------------\n";
                        //break;
                    }
                    file.close();
                    it++;
                }
            }
        }
    }
    closedir(dir);
}

std::unordered_map<std::string, std::string> virusdatabasen(){
    //Maps all the virusname(key) with the asciivalues(value) and return that map
    std::ifstream rFile("/home/erik/c++/antiviruslab/signatures.db");
    std::unordered_map<std::string, std::string> vsd;

    if (rFile.is_open()){
        while (rFile.good()){
            std::string virusname, hexvalue, asciivalue;
            std::getline(rFile, virusname, '=');
            if ((virusname.size() > 32) || (virusname == "")){
                std::cout << "The virus has no name or the name is longer than 32 characters" << std::endl;
                continue;
            }
            std::getline(rFile, hexvalue, '\n');
            asciivalue = hextoascii(hexvalue);
            vsd[virusname] = asciivalue;
        }
        return vsd;
    }
}