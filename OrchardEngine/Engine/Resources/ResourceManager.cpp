#include "ResourceManager.hpp"
#include <fstream>

using namespace orchard;

ResourceManager::ResourceManager() = default;

void ResourceManager::mountPackage(const std::string& orchardPkg) {
    std::ifstream file(orchardPkg, std::ios::binary);
    if (!file) {
        return;
    }
    uint32_t count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (uint32_t i = 0; i < count; ++i) {
        AssetRecord record;
        uint32_t uuidLen = 0;
        file.read(reinterpret_cast<char*>(&uuidLen), sizeof(uuidLen));
        record.uuid.resize(uuidLen);
        file.read(record.uuid.data(), uuidLen);
        file.read(reinterpret_cast<char*>(&record.offset), sizeof(record.offset));
        file.read(reinterpret_cast<char*>(&record.length), sizeof(record.length));
        m_database.addRecord(record);
    }
}

std::vector<uint8_t> ResourceManager::loadBinary(const std::string& uuid) const {
    const AssetRecord* record = m_database.find(uuid);
    if (!record) {
        return {};
    }
    std::ifstream file(record->path, std::ios::binary);
    if (!file) {
        return {};
    }
    file.seekg(record->offset, std::ios::beg);
    std::vector<uint8_t> data(record->length);
    file.read(reinterpret_cast<char*>(data.data()), record->length);
    return data;
}
