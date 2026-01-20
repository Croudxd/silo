#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include "database.h"
#include "vault.h"
#include "silo.h"

/*
 *
 * Idea of this project is to speed up moving files.
 * Currently when we move files we need to type mv address/ address which is long and boring.
 * We want to be able to stash/push a file into a temp directory and then we can pop where we want it to be. 
 * We can do this with multiple files in several buffers so we can do 
 *
 * silo push buffer1 file1 file2 file3 file4
 * silo pop buffer1
 *
 * silo pop buffer1 file1
 *
 * silo list
 *
 * silo clear
 *
 */
namespace fs = std::filesystem;

static fs::path path = "/home/ben/temp";

static std::string_view HELP_MESSAGE = 
    "Silo - A minimalist file stashing utility\n\n"
    "Usage:\n"
    "  silo push <buffer> <path>    Stash a file into a named buffer\n"
    "  silo pop  <buffer> <path>    Restore the most recent file from a buffer\n"
    "  silo list                    Show all buffers and stashed files\n"
    "  silo help                    Show this message\n\n"
    "Examples:\n"
    "  silo push work report.pdf\n"
    "  silo pop work\n";


int main (int argc, char* argv[])
{
    if ( argc <= 2 ) 
    { 
        std::cout << HELP_MESSAGE;
        return 0;
    }

    std::vector<std::string> args(argv, argv + argc);

    fs::path cwd = fs::current_path();
    Vault v = { path };
    Database db;
    Silo s = {v, db, cwd};
    if ( !db.init() ) return 0;
    auto &map = s.get_map();

    std::string commandName = args[1];

    if (map.contains(commandName)) {
        map[commandName](args); // Call the function
    } else {
        std::cerr << "Unknown command: " << commandName << "\n";
        std::cout << HELP_MESSAGE;
    }
    

    return 0;
}

