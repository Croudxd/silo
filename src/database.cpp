#include "database.h"
#include <sqlite3.h>
#include "storage.h"
#include "vault.h"
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

int Database::push (std::string buffer, std::string file_path)
{
    if ( db == nullptr ) return -1;

    const char* b_sql = "INSERT OR IGNORE INTO buffers (buffer_name) VALUES (?);";
    sqlite3_stmt* b_stmt;
    
    if (sqlite3_prepare_v2(db, b_sql, -1, &b_stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(b_stmt, 1, buffer.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(b_stmt);
        sqlite3_finalize(b_stmt);
    }

    fs::path source_path = fs::absolute(file_path);
    if (!fs::exists(source_path)) return -1;

    const char* f_sql = "INSERT INTO files (buffer_name, original_path, filename) VALUES (?, ?, ?);";
    sqlite3_stmt* f_stmt;

    if (sqlite3_prepare_v2(db, f_sql, -1, &f_stmt, nullptr) != SQLITE_OK) return -1;

    sqlite3_bind_text(f_stmt, 1, buffer.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(f_stmt, 2, source_path.string().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(f_stmt, 3, source_path.filename().string().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(f_stmt) != SQLITE_DONE) {
        sqlite3_finalize(f_stmt);
        return -1;
    }

    sqlite3_finalize(f_stmt);



    return 0;
}

int Database::pop (std::string buffer, std::string file_path)
{

    return 0;
}



