#include "UnitExtensions.h"

bool UnitExtensions::HasAuraByTypeId(CGUnit* unit, uint32_t auraType) {
    uint32_t auraLength = unit->auras.length;

    if (auraLength) {
        for (uint32_t i = 0; i < auraLength; i++) {
            SpellRow buffer;
            uint32_t spellId = unit->auras.auraList[i].spellId;

            if (!spellId)
                continue;

            if (ClientDB::GetLocalizedRow(reinterpret_cast<void*>(0xAD49D0), spellId, &buffer) && SpellRec_C::HasAura(&buffer, auraType))
                return true;
        }
    }

    return false;
}
