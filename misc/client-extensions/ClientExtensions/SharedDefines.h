#pragma once

#include "Util.h"
#include "WowClient/C2Vector.h"
#include "WowClient/C3Vector.h"

struct lua_State;

static uint32_t dummy = 0;

static char* sConnectorPlus = " + ";
static char* sPluralS = "s";
static char* sSpace = " ";

// structs
struct gtCombatRatingsRow {
    uint32_t ID;
    float data;
};

struct gtOCTClassCombatRatingScalarRow {
    uint32_t ID;
    float data;
};

// Aleist3r: this is not a full struct afaik but that's what's needed in dll
// will update if more fields are required
struct WoWTime {
    int32_t minute;
    int32_t hour;
    int32_t weekDay;
    int32_t monthDay;
    int32_t month;
    int32_t year;
    int32_t flags;
};

struct ZoneLightData
{
    int32_t mapID;
    int32_t lightID;
    void* pointData;
    int32_t pointNum;
    float minX;
    float minY;
    float maxX;
    float maxY;
};

struct OcclusionVolumeData
{
    int32_t mapID;
    int32_t flags;
    C3Vector min;
    C3Vector max;
    void* pointData;
    int32_t pointNum;
};

struct TSLink
{
    TSLink* m_prevlink;
    void* m_next;
};

struct TSList
{
    ptrdiff_t m_linkoffset;
    TSLink m_terminator;
};

struct RCString
{
    void** vtable;
    DWORD ukn1;
    char* string;
};

struct WorldHitTest
{
    uint64_t guid;
    C3Vector hitpoint;
    float distance;
    C3Vector start;
    C3Vector end;
};

struct CSimpleTop
{
    char pad1[0x78];
    void* mouseFocus;
    char pad2[0x11A8];
    C2Vector mousePosition;
};

struct CGWorldFrame
{
    char pad1[0xA0];
    CSimpleTop* simpleTop;
    char pad2[0x234];
    uint32_t ukn16;
    uint32_t ukn17;
    WorldHitTest m_actionHitTest;
};

struct PendingSpellCastData
{
    char pad0[0x18];
    uint32_t spellId;
};

struct PendingSpellCast
{
    char pad0[0x8];
    PendingSpellCastData data;
};
