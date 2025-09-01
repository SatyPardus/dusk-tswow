#pragma once

#include "ClientMacros.h"
#include "WowClient/WGUID.h"
#include "WowClient/MovementInfo.h"
#include "WowClient/DBC/SpellRow.h"
#include "WowClient/Entities/CGObject.h"
#include "WowClient/Spells/AuraData.h"

struct CGUnit;
namespace CGUnit_C
{
    CLIENT_FUNCTION(GetShapeshiftFormId, 0x71AF70, __thiscall, uint32_t, (CGUnit*))
    CLIENT_FUNCTION(HasAuraBySpellId, 0x7282A0, __thiscall, bool, (CGUnit*, uint32_t))
    CLIENT_FUNCTION(GetAuraCount, 0x004F8850, __thiscall, int, (CGUnit*))
    CLIENT_FUNCTION(GetAura, 0x00556E10, __thiscall, AuraData*, (CGUnit*, uint32_t))
    CLIENT_FUNCTION(GetAuraFlags, 0x00565510, __thiscall, uint8_t, (CGUnit*, uint32_t))
    CLIENT_FUNCTION(AffectedByAura, 0x007283A0, __thiscall, char, (CGUnit*, uint32_t, uint32_t))
    CLIENT_FUNCTION(HasAuraMatchingSpellClass, 0x7283A0, __thiscall, bool, (CGUnit*, uint32_t, SpellRow*))
    CLIENT_FUNCTION(ShouldFadeIn, 0x716650, __thiscall, bool, (CGUnit*))
    CLIENT_FUNCTION(GetDistanceToPos, 0x004F61D0, __thiscall, float, (CGUnit*, C3Vector*))
}

struct UnitBytes0
{
    uint8_t raceID;
    uint8_t classID;
    uint8_t genderID;
    uint8_t powerTypeID;
};

struct UnitBytes1
{
    uint8_t standState;
    uint8_t petTalents;
    uint8_t visFlags;
    uint8_t animTier;
};

struct UnitBytes2
{
    uint8_t sheathState;
    uint8_t pvpFlag;
    uint8_t petFlags;
    uint8_t shapeshift;
};

struct UnitFields
{
    WGUID UNIT_FIELD_CHARM;
    WGUID UNIT_FIELD_SUMMON;
    WGUID UNIT_FIELD_CRITTER;
    WGUID UNIT_FIELD_CHARMEDBY;
    WGUID UNIT_FIELD_SUMMONEDBY;
    WGUID UNIT_FIELD_CREATEDBY;
    WGUID UNIT_FIELD_TARGET;
    WGUID UNIT_FIELD_CHANNEL_OBJECT;
    uint32_t UNIT_CHANNEL_SPELL;
    UnitBytes0 UNIT_FIELD_BYTES_0;
    uint32_t UNIT_FIELD_HEALTH;
    uint32_t UNIT_FIELD_POWERS[7];
    uint32_t UNIT_FIELD_MAXHEALTH;
    uint32_t UNIT_FIELD_MAXPOWERS[7];
    float UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER[7];
    float UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER[7];
    uint32_t UNIT_FIELD_LEVEL;
    uint32_t UNIT_FIELD_FACTIONTEMPLATE;
    uint32_t UNIT_VIRTUAL_ITEM_SLOT_ID[3];
    uint32_t UNIT_FIELD_FLAGS;
    uint32_t UNIT_FIELD_FLAGS_2;
    uint32_t UNIT_FIELD_AURASTATE;
    uint32_t UNIT_FIELD_BASEATTACKTIME[2];
    uint32_t UNIT_FIELD_RANGEDATTACKTIME;
    float UNIT_FIELD_BOUNDINGRADIUS;
    float UNIT_FIELD_COMBATREACH;
    uint32_t UNIT_FIELD_DISPLAYID;
    uint32_t UNIT_FIELD_NATIVEDISPLAYID;
    uint32_t UNIT_FIELD_MOUNTDISPLAYID;
    float UNIT_FIELD_MINDAMAGE;
    float UNIT_FIELD_MAXDAMAGE;
    float UNIT_FIELD_MINOFFHANDDAMAGE;
    float UNIT_FIELD_MAXOFFHANDDAMAGE;
    UnitBytes1 UNIT_FIELD_BYTES_1;
    uint32_t UNIT_FIELD_PETNUMBER;
    uint32_t UNIT_FIELD_PET_NAME_TIMESTAMP;
    uint32_t UNIT_FIELD_PETEXPERIENCE;
    uint32_t UNIT_FIELD_PETNEXTLEVELEXP;
    uint32_t UNIT_DYNAMIC_FLAGS;
    float UNIT_MOD_CAST_SPEED;
    uint32_t UNIT_CREATED_BY_SPELL;
    uint32_t UNIT_NPC_FLAGS;
    uint32_t UNIT_NPC_EMOTESTATE;
    uint32_t UNIT_FIELD_STAT0;
    uint32_t UNIT_FIELD_STAT1;
    uint32_t UNIT_FIELD_STAT2;
    uint32_t UNIT_FIELD_STAT3;
    uint32_t UNIT_FIELD_STAT4;
    uint32_t UNIT_FIELD_POSSTAT0;
    uint32_t UNIT_FIELD_POSSTAT1;
    uint32_t UNIT_FIELD_POSSTAT2;
    uint32_t UNIT_FIELD_POSSTAT3;
    uint32_t UNIT_FIELD_POSSTAT4;
    uint32_t UNIT_FIELD_NEGSTAT0;
    uint32_t UNIT_FIELD_NEGSTAT1;
    uint32_t UNIT_FIELD_NEGSTAT2;
    uint32_t UNIT_FIELD_NEGSTAT3;
    uint32_t UNIT_FIELD_NEGSTAT4;
    uint32_t UNIT_FIELD_RESISTANCES[7];
    uint32_t UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE[7];
    uint32_t UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE[7];
    uint32_t UNIT_FIELD_BASE_MANA;
    uint32_t UNIT_FIELD_BASE_HEALTH;
    UnitBytes2 UNIT_FIELD_BYTES_2;
    uint32_t UNIT_FIELD_ATTACK_POWER;
    uint16_t UNIT_FIELD_ATTACK_POWER_MODS[2];
    float UNIT_FIELD_ATTACK_POWER_MULTIPLIER;
    uint32_t UNIT_FIELD_RANGED_ATTACK_POWER;
    uint16_t UNIT_FIELD_RANGED_ATTACK_POWER_MODS[2];
    float UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER;
    float UNIT_FIELD_MINRANGEDDAMAGE;
    float UNIT_FIELD_MAXRANGEDDAMAGE;
    uint32_t UNIT_FIELD_POWER_COST_MODIFIER[7];
    float UNIT_FIELD_POWER_COST_MULTIPLIER[7];
    float UNIT_FIELD_MAXHEALTHMODIFIER;
    float UNIT_FIELD_HOVERHEIGHT;
    uint32_t UNIT_FIELD_PADDING;
};

class CGUnit : public CGObject
{
  public:
    UnitFields* unitData;
    uint32_t ukn1;
    MovementInfo* movementInfo;
    uint32_t ukn3[612];
    uint32_t currentCastId;
    uint32_t ukn5[4];
    uint32_t currentChannelId;
    uint32_t ukn7[350];
};
