#include "silo.h"
#include <iostream>


Silo::~Silo()
{

}

void Silo::pop(const std::vector<std::string> &args)
{
}

void Silo::push(const std::vector<std::string> &args)
{

    if ( args.size() < 4)
    {
        std::cerr << "Error: No arguments \n" << "silo push <buffer> <path>    Stash a file into a named buffer\n"; 
        return ;
    }

    std::string buffer = args[2];
    for ( auto x = 3; x < args.size(); x++)
    { 
        auto file_path = cwd.string()+"/"+args[x];
        db.push(buffer, file_path) ;
        v.push(file_path, args[x]) ;
    }
}

