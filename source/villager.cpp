#include "villager.h"

Villager::Villager() { }

Villager::~Villager() {
    // Checking if a pointer is null is not necessary for delete. It will verify the memory is valid before attempting to delete it.
    if (this->m_villagerData != nullptr) {
        delete this->m_villagerData;
    }
}

Villager::Villager(const u32 offset, const u32 index) : m_offset(offset), m_index(index), m_villagerData(new Villager_s) {
    Save::Instance()->ReadArray(reinterpret_cast<u8 *>(this->m_villagerData), offset, sizeof(Villager_s));
}

u32 Villager::GetOffset() const {
    return this->m_offset;
}

u32 Villager::GetIndex() const {
    return this->m_index;
}

u16 Villager::GetId() const {
    return this->m_villagerData->Id;
}