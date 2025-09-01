#pragma once

struct SkillLineRow
{
    uint32_t m_ID;
    uint32_t m_categoryID;
    uint32_t m_skillCostsID;
    char* m_displayName_lang;
    char* m_description_lang;
    uint32_t m_spellIconID;
    char* m_alternateVerb_lang;
    uint32_t m_canLink;
};
