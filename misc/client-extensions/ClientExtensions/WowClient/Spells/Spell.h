#pragma once

#include "WowClient/DBC/SpellRow.h"

namespace Spell_C {
    CLIENT_FUNCTION(SpellFailed, 0x808200, __cdecl, void, (void*, SpellRow*, uint32_t, int32_t, int32_t, uint32_t))
    CLIENT_FUNCTION(IsTargeting, 0x007FD620, __cdecl, bool, ())
    CLIENT_FUNCTION(CanTargetTerrain, 0x007FD750, __cdecl, bool, ())
    CLIENT_FUNCTION(CanTargetUnits, 0x007FD650, __cdecl, bool, ())
    CLIENT_FUNCTION(GetSpellRange, 0x00802C30, __cdecl, void, (void* a1, unsigned int spellId, float* minDist, float* maxDist, void* a5))
}
