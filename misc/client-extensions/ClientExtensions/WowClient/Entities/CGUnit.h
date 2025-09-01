#pragma once

#include "ClientMacros.h"
#include "WowClient/WGUID.h"
#include "WowClient/MovementInfo.h"
#include "WowClient/DBC/SpellRow.h"
#include "WowClient/Entities/CGObject.h"
#include "WowClient/Spells/AuraData.h"

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

    uint32_t GetShapeshiftFormId()
    {
        return ((uint32_t(__thiscall*)(CGUnit*))0x0071AF70)(this);
    }

    bool HasAuraBySpellId(uint32_t a2)
    {
        return ((bool(__thiscall*)(CGUnit*, uint32_t))0x007282A0)(this, a2);
    }

    int GetAuraCount()
    {
        return ((int(__thiscall*)(CGUnit*))0x004F8850)(this);
    }

    AuraData* GetAura(uint32_t a2)
    {
        return ((AuraData*(__thiscall*)(CGUnit*, uint32_t))0x00556E10)(this, a2);
    }

    uint8_t GetAuraFlags(uint32_t a2)
    {
        return ((uint8_t(__thiscall*)(CGUnit*, uint32_t))0x00565510)(this, a2);
    }

    bool HasAuraMatchingSpellClass(uint32_t a2, SpellRow* a3)
    {
        return ((bool(__thiscall*)(CGUnit*, uint32_t, SpellRow*))0x007283A0)(this, a2, a3);
    }

    bool ShouldFadeIn()
    {
        return ((bool(__thiscall*)(CGUnit*))0x00716650)(this);
    }

    float GetDistanceToPos(C3Vector* a2)
    {
        return ((float(__thiscall*)(CGUnit*, C3Vector*))0x004F61D0)(this, a2);
    }
};
