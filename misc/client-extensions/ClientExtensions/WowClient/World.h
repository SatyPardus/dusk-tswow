#pragma once

#include "SharedDefines.h"

namespace World_C {
    inline int32_t getMapId() { return *reinterpret_cast<int32_t*>(0xADFBC4); }

    CLIENT_FUNCTION(LoadMap, 0x781430, __cdecl, void, (char*, C3Vector*, uint32_t))
    CLIENT_FUNCTION(UnloadMap, 0x783180, __cdecl, void, ())
}
