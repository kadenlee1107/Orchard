#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "AssetDatabase.hpp"

namespace orchard {

class ResourceManager {
public:
    ResourceManager();

    void mountPackage(const std::string& orchardPkg);
    std::vector<uint8_t> loadBinary(const std::string& uuid) const;

private:
    AssetDatabase m_database;
};

}
