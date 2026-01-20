#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include "database.h"

namespace fs = std::filesystem;

int main (int argc, char* argv[])
{

    Database db;
    if ( !db.init() ) return 0;

    std::vector<std::string> args(argv, argv + argc);

    if ( argc <= 2 ) 
    { 
        std::cout << "use more inputs dumbass";
        return 0;
    }

    //grab the current working directory.
    fs::path cwd = fs::current_path();

    std::string buffer = args[1];

    std::vector<std::string> files ;
    for ( auto& file : args) files.push_back(file);

    

    return 0;
}

