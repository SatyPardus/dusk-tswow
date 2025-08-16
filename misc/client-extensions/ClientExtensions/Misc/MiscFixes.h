#pragma once

#include "SharedDefines.h"
#include <unordered_map>
#include <unordered_set>

class MiscFixes {
public:
    static void SetYearOffsetMultiplier();
    static inline std::unordered_map<void*, float> g_models_original_alphas;
    static inline std::unordered_set<void*> g_models_current;
    static inline std::unordered_set<void*> g_models_being_faded;
    static inline int g_models_cleanup_timer = 0;
    static inline bool g_models_collision_check = false;
    static inline CVar* g_models_alpha_cvar;

  private:
    static void Apply();
    static bool __fastcall ShouldObjectFadeIn(CGObject* _this, uint32_t unused);
    static void UpdateObjectVtable();
    static void UpdateWoWTimeFunctions();
    static void CameraCollisionFade();

    static char* GetTimeString(WoWTime* a1, char* a2, uint32_t a3);
    static void PackTimeDataToDword(uint32_t* packedTime, int32_t minute, int32_t hour, int32_t weekDay, int32_t monthDay, int32_t month, int32_t year, int32_t flags);
    static void PackWoWTimeToDword(uint32_t* dword, WoWTime* time);
    static void UnpackWoWTime(uint32_t packedTime, int32_t* minute, int32_t* hour, int32_t* weekDay, int32_t* monthDay, int32_t* month, int32_t* year, int32_t* flags);

    static char CGWorldFrame_Intersect(C3Vector* start, C3Vector* end, C3Vector* hitPoint, float* distance, uint32_t flag, uint32_t buffer);
    static char ModelsAlpha_CVarCallback(CVar* cvar, const char*, const char* value, const char*);

    friend class ClientExtensions;

    static inline uint32_t yearOffsetMult = 0;
};
