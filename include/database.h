#pragma once
#include <string>
#include <sqlite3.h>
#include <vector>


class Database
{
    private:
        sqlite3* db;

    public:
       Database () : db(nullptr) {}
       bool init ();
       ~Database ();
       int push (std::string buffer, std::string file_path);
       int remove_file(std::string buffer, std::string filename);
       std::vector<std::string> pop (std::string buffer, std::string file_path);
       std::string get_path ();
};
