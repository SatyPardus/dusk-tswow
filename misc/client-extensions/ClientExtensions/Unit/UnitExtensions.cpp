#include "Unit/UnitExtensions.h"
#include "Logger.h"

bool UnitExtensions::HasAuraByTypeId(void* unit, uint32_t auraType) {
    bool result = false;
    uint32_t buffer[170] = { 0 };
    uint32_t auraCount = CGUnit_C__GetAuraCount(unit);
    std::vector<uint32_t> spellIds = {};
    uintptr_t* thisPtr = reinterpret_cast<uintptr_t*>(unit);

    if (auraCount) {
    //    uint32_t length = *(thisPtr + 884);
    //    LOG_DEBUG << "length: " << length;
    //    if (length == -1)
    //        length = *(thisPtr + 789);
    //
    //    for (uint32_t i = 0; i < length; i++) {
    //        //                 auraTable.length        auraTable.auras[0].spellID          auraTable
    //        uint32_t auraPtr = *(thisPtr + 884) == -1 ? *(thisPtr + 790) + 24 * i : *(thisPtr + 788) + 24 * i;
    //
    //        if (*reinterpret_cast<uint32_t*>(auraPtr + 8))
    //            spellIds.push_back(*reinterpret_cast<uint32_t*>(auraPtr + 8));
    //    }
    //
    //    for (uint32_t j = 0; j < spellIds.size(); j++) {
    //        LOG_DEBUG << "Spell ID: " << spellIds[j];
    //        if (ClientDB__GetLocalizedRow((void*)0xAD49D0, spellIds[j], &buffer)) {
    //            for (uint8_t k = 0; k < 3; k++) {
    //                if (buffer[95 + k] == auraType) {
    //                    result = true;
    //                    break;
    //                }
    //            }
    //        }
    //
    //        if (result)
    //            break;
    //    }
    }

    return result;
}
