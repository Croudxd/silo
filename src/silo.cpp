#include "silo.h"
#include <vector>
#include <iostream>


Silo::~Silo()
{

}
void Silo::pop(const std::vector<std::string> &args)
{

    if ( args.size() < 3)
    {
        std::cerr << "Error: No buffer specified \n" << "silo pop  <buffer> Restore all files\n";
        return ;
    }
    if ( args.size() == 3)
    { 
        std::vector<std::string> vec = db.pop(args[2], "");
        v.pop(cwd, vec);
        db.remove_file(args[2], "");
        return;
    }
    if ( args.size() == 4)
    { 
        std::vector<std::string> vec = db.pop(args[2], args[3]);
        v.pop(cwd, vec);
        db.remove_file(args[2], args[3]);
        return;
    }
    else {
        std::cerr << "Error: path specified";
        return;
    }
}

void Silo::push(const std::vector<std::string> &args)
{

    if ( args.size() < 4)
    {
        std::cerr << "Error: No paths specified \n" << "silo push <buffer> <path>    Stash a file into a named buffer\n"; 
        return ;
    }

    std::string buffer = args[2];
    for ( size_t x = 3; x < args.size(); x++)
    { 
        auto file_path = cwd / args[x];
        db.push(buffer, file_path) ;
        v.push(file_path, args[x]) ;
    }
}

void Silo::list(const std::vector<std::string> &args)
{
    if ( args.size() == 2)
    {
        auto buffers = db.list_buffers();
        for ( auto& name : buffers)
        {
            std::cout << name << std::endl;
        }
    }
    else
    {
        auto buffers = db.pop(args[2], "");
        for ( auto& name : buffers)
        {
            std::cout << name << std::endl;
        }
    }
}
