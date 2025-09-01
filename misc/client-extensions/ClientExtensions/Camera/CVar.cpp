#include "ClientLua.h"
#include "ClientDetours.h"
#include "SharedDefines.h"

enum CVarFlags : uint32_t {
    CVarFlags_ReadOnly = 0x4,
    CVarFlags_CheckTaint = 0x8,
    CVarFlags_HideFromUser = 0x40,
    CVarFlags_ReadOnlyForUser = 0x100,

};

inline CVar* GetCVar(const char* name) { return ((decltype(&GetCVar))0x00767460)(name); }
inline CVar* FindCVar(const char* name) { return ((decltype(&FindCVar))0x00767440)(name); }
