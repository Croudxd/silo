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

fs::path get_storage_path()
{
    const char* xdg_data = std::getenv("XDG_DATA_HOME");
    fs::path base_path;

    if (xdg_data) {
        base_path = fs::path(xdg_data);
    } else {
        const char* home = std::getenv("HOME");
        if (!home) {
            std::cerr << "Warning: HOME environment variable not set, using ~/.silo/storage\n";
            return fs::path(".silo") / "storage";
        }
        base_path = fs::path(home) / ".local" / "share";
    }

    fs::path storage_dir = base_path / "silo" / "storage";

    if (!fs::exists(storage_dir)) {
        fs::create_directories(storage_dir);
    }

    return storage_dir;
}

constexpr std::string_view HELP_MESSAGE = 
    "Silo - Minimalist file stashing\n\n"
    "Usage:\n"
    "  silo stash <buffer> <path>    Push a file into a buffer\n"
    "  silo pop   <buffer> [file...] Restore all files, or specific ones\n"
    "  silo list  [buffer]           List all buffers or files in a buffer\n"
    "  silo help                     Show this message\n\n"
    "Examples:\n"
    "  silo pop work                 # Restores everything in 'work'\n"
    "  silo pop work notes.txt       # Restores only 'notes.txt'\n";


int main (int argc, char* argv[])
{
    if ( argc < 2 ) 
    { 
        std::cerr << HELP_MESSAGE;
        return 0;
    }

    std::vector<std::string> args(argv, argv + argc);

    fs::path cwd = fs::current_path();
    Vault v = { get_storage_path() };
    Database db;
    Silo s = {v, db, cwd};
    if ( !db.init() ) return 0;
    auto &map = s.get_map();

    std::string commandName = args[1];

    if (map.contains(commandName)) {
        map[commandName](args);
    } else {
        std::cerr << "Unknown command: " << commandName << "\n";
        std::cerr << HELP_MESSAGE;
    }

    

    return 0;
}

