#pragma once

#include "SharedDefines.h"
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>

class Spells {
  public:
    static inline bool s_castAtCursor = false;
    static inline CVar* g_spell_min_clip_distance_percentage_cvar;

  private:
    static void Apply();
    static char SpellMinClipDistancePercentage_CVarCallback(CVar* cvar, const char*, const char* value, const char*);

    friend class ClientExtensions;
};
