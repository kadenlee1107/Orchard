#include "AssetDatabase.hpp"

using namespace orchard;

void AssetDatabase::addRecord(const AssetRecord& record) {
    m_records[record.uuid] = record;
}

const AssetRecord* AssetDatabase::find(const std::string& uuid) const {
    auto it = m_records.find(uuid);
    return it == m_records.end() ? nullptr : &it->second;
}
