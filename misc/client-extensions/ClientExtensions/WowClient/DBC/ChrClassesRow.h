#pragma once

struct ChrClassesRow
{
    uint32_t m_ID;
    uint32_t m_DisplayPower;
    char* m_petNameToken;
    char* m_name_lang;
    char* m_name_female_lang;
    char* m_name_male_lang;
    char* m_filename;
    uint32_t m_spellClassSet;
    uint32_t m_flags;
    uint32_t m_cinematicSequenceID;
    uint32_t m_required_expansion;
    uint32_t m_attackPowerPerStrength;
    uint32_t m_attackPowerPerAgility;
    uint32_t m_rangedAttackPowerPerAgility;
};
