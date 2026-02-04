#pragma once
#include<unordered_map>
#include<string>
#include<functional>
#include<vector>
#include <filesystem>
#include"vault.h"
#include"database.h"

namespace fs = std::filesystem;

class Silo
{
    public:

        using function = std::function<void(const std::vector<std::string>&)>;

        Silo(Vault &v, Database &db, fs::path &cwd) : v(v),  db(db), cwd(cwd)
        {
            this->map = {
                {"stash", [this](auto& args) { push(args); }},
                {"s",    [this](auto& args) { push(args); }},

                {"pop",  [this](auto& args) { pop(args); }},
                {"p"  ,  [this](auto& args) { pop(args); }},

                {"list", [this](auto& args) { list(args); }},
            };       

       }

        ~Silo();
        std::unordered_map<std::string, function>& get_map() { return this->map; };

    private:
        std::unordered_map<std::string, function> map;
        Vault &v;
        Database &db;
        fs::path &cwd;
        void pop(const std::vector<std::string> &args);
        void push(const std::vector<std::string> &args);
        void list(const std::vector<std::string> &args);
};

