#pragma once

struct MapRow
{
    uint32_t m_ID;
    char* m_Directory;
    uint32_t m_InstanceType;
    uint32_t m_Flags;
    uint32_t m_PVP;
    char* m_MapName_lang;
    uint32_t m_areaTableID;
    char* m_MapDescription0_lang;
    char* m_MapDescription1_lang;
    uint32_t m_LoadingScreenID;
    float m_minimapIconScale;
    uint32_t m_corpseMapID;
    float m_corpseX;
    float m_corpseY;
    uint32_t m_timeOfDayOverride;
    uint32_t m_expansionID;
    uint32_t m_raidOffset;
    uint32_t m_maxPlayers;
    uint32_t m_parentMapID;
};
