#include "database.h"
#include "sqlite3.h"
#include "storage.h"
#include <string>
#include <iostream>


Database::~Database()
{
    if (db != nullptr) 
    {
        sqlite3_close (db);
    }
}

bool Database::init()
{
    std::string path = get_db_path().string();
    if (sqlite3_open(path.c_str(), &db ) != SQLITE_OK)
    {
        std::cerr << "Error opening DB:" << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    const char* sql = 
        "PRAGMA foreign_keys = ON;" 
        "CREATE TABLE IF NOT EXISTS buffers ("
        "  buffer_index INTEGER PRIMARY KEY"
        ");"
        "CREATE TABLE IF NOT EXISTS files ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  buffer_index TEXT NOT NULL,"
        "  original_path TEXT NOT NULL,"
        "  filename TEXT NOT NULL,"
        "  timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "  FOREIGN KEY(buffer_index) REFERENCES buffers(buffer_index) ON DELETE CASCADE"
        ");";


    char* errorMessage = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

int Database::add (std::string buffer, std::string file_path)
{
    if ( db == nullptr ) return -1;
    const char *sql = "";

    char* errorMessage = nullptr;
    if ( sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK )
    {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return -1;
    }

    return 0;
}



