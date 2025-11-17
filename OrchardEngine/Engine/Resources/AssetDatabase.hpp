#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace orchard {

struct AssetRecord {
    std::string uuid;
    std::string path;
    uint64_t offset;
    uint64_t length;
};

class AssetDatabase {
public:
    void addRecord(const AssetRecord& record);
    const AssetRecord* find(const std::string& uuid) const;

private:
    std::unordered_map<std::string, AssetRecord> m_records;
};

}
