
#include <filesystem>
#include <cstdlib>
#include <iostream>

namespace fs = std::filesystem;

fs::path get_db_path()
{
    const char* xdg_data = std::getenv("XDG_DATA_HOME");
    //Verify the .db file is in normal location. If it is cool else give error.
    fs::path base_path;

    if (xdg_data) {
        base_path = fs::path(xdg_data);
    } else {
        const char* home = std::getenv("HOME");
        if (!home) return "silo.db";
        base_path = fs::path(home) / ".local" / "share";
    }

    fs::path silo_dir = base_path / "silo";

    if (!fs::exists(silo_dir)) {
        fs::create_directories(silo_dir);
    }

    return silo_dir / "silo.db";
}


