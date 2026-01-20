#include "vault.h"
#include <vector>
#include <iostream>


Vault::Vault(fs::path storage)
{
    this->storage = storage;
}

Vault::~Vault()
{

} 

bool Vault::push(const fs::path& source, std::string name)
{
    if (relocate_file(source, storage.string()+"/"+name)) 
    {
        return true;
    }
    else {
        return false;
    }
}

bool Vault::pop(const fs::path& destination, std::vector<std::string> names)
{
    if (!names.empty())
    {
        bool all_success = true;
        for (auto& name : names)
        {
            if(!relocate_file(storage.string()+"/"+name, destination.string()+"/"+name))
            {
                all_success = false;
            }
        }
        return all_success;
    }
    return false;
}

bool Vault::relocate_file(const fs::path& source, const fs::path& destination) 
{
    try {
        if (destination.has_parent_path()) {
            fs::create_directories(destination.parent_path());
        }

        fs::rename(source, destination);
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "File system error: " << e.what() << std::endl;
        return false;
    }
}
