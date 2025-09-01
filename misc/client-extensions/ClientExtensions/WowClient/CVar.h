#pragma once

#include "ClientMacros.h"
#include "SharedDefines.h"

enum CVarFlags : uint32_t
{
    CVarFlags_ReadOnly        = 0x4,
    CVarFlags_CheckTaint      = 0x8,
    CVarFlags_HideFromUser    = 0x40,
    CVarFlags_ReadOnlyForUser = 0x100,

};

struct CVar;
typedef char(__cdecl* CVarCallback)(CVar*, const char*, const char*, const char*);
struct CVar
{
    DWORD pad[0x18];
    DWORD m_category;
    DWORD m_flags;
    RCString m_stringValue;
    float m_numberValue;
    int m_intValue;
    int m_modified;
    RCString m_defaultValue;
    RCString m_resetValue;
    RCString m_latchedValue;
    RCString m_help;
    CVarCallback m_callback;
    void* m_arg;
};

namespace CVar_C {
    /// <summary>
    /// Registers a CVar to the game CVar storage.
    /// Usage: CVar::Register(name, description, flags, default value, callback, category, setResetValue, callback arg, register)
    /// </summary>
    CLIENT_FUNCTION(Register, 0x00767FC0, __cdecl, CVar*, (char*, char*, int, char*, CVarCallback, int, char, int, char))

    /// <summary>
    /// Retrieves a CVar that was registered on creation
    /// </summary>
    CLIENT_FUNCTION(LookupRegistered, 0x00767460, __cdecl, CVar*, (char*))

    /// <summary>
    /// Retrieves any CVar
    /// </summary>
    CLIENT_FUNCTION(Lookup, 0x00767440, __cdecl, CVar*, (char*))

    /// <summary>
    /// Sets the current CVar value.
    /// Usage: CVar::Set(cvar, value, setValue, setResetValue, setDefaultValue, needSave)
    /// </summary>
    CLIENT_FUNCTION(Set, 0x766940, __thiscall, void, (CVar*, char*, char, char, char, char))
}
