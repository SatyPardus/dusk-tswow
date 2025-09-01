#pragma once

struct SkillLineAbilityRow
{
    uint32_t m_ID;
    uint32_t m_skillLine;
    uint32_t m_spell;
    uint32_t m_raceMask;
    uint32_t m_classMask;
    uint32_t m_excludeRace;
    uint32_t m_excludeClass;
    uint32_t m_minSkillLineRank;
    uint32_t m_supercededBySpell;
    uint32_t m_acquireMethod;
    uint32_t m_trivialSkillLineRankHigh;
    uint32_t m_trivialSkillLineRankLow;
    uint32_t m_characterPoints[2];
    uint32_t m_numSkillUps;
};
