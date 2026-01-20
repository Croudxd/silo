#pragma once
#include <vector>
#include <filesystem>


namespace fs = std::filesystem;

class Vault
{
    public:
        Vault (fs::path storage) ;   
        ~Vault ();   
        bool push(const fs::path& destination, std::string name);
        bool pop(const fs::path& destination, std::vector<std::string> name);

    private:
        bool relocate_file(const fs::path& source, const fs::path& destination); 
        fs::path storage;
};
