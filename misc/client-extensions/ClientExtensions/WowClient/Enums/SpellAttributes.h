#pragma once

enum SpellAttr0 : uint32_t
{
    SPELL_ATTR0_REQ_AMMO          = 0x00000002,
    SPELL_ATTR0_ON_NEXT_SWING     = 0x00000004,
    SPELL_ATTR0_ABILITY           = 0x00000010,
    SPELL_ATTR0_TRADESPELL        = 0x00000020,
    SPELL_ATTR0_PASSIVE           = 0x00000040,
    SPELL_ATTR0_HIDDEN_CLIENTSIDE = 0x00000080,
    SPELL_ATTR0_ON_NEXT_SWING_2   = 0x00000400,
};

enum SpellAttr1 : uint32_t
{
    SPELL_ATTR1_CHANNELED_1 = 0x00000004,
    SPELL_ATTR1_CHANNELED_2 = 0x00000040,
};

enum SpellAttr2 : uint32_t
{
    SPELL_ATTR2_AUTOREPEAT_FLAG = 0x00000020,
};

enum SpellAttr3 : uint32_t
{
    SPELL_ATTR3_MAIN_HAND   = 0x00000400,
    SPELL_ATTR3_REQ_OFFHAND = 0x01000000,
};

enum SpellAttr0Custom : uint32_t
{
    SPELL_ATTR0_CU_TREAT_AS_INSTANT   = 0x00000001, // Changes tooltip line responsible for cast time to "Instant"
    SPELL_ATTR0_CU_FORCE_HIDE_CASTBAR = 0x00000002, // Does not display cast bar
    SPELL_ATTR0_CU_DO_NOT_DISPLAY_POWER_COST = 0x00000004, // Does not display power cost in tooltip
    SPELL_ATTR0_CU_SUPPRESS_LEARN_MSG        = 0x00000008, // Does not display "You have learned a new spell:" message
    SPELL_ATTR0_CU_SUPPRESS_UNLEARN_MSG      = 0x00000010, // Does not display "You have unlearned" message
    SPELL_ATTR0_CU_INVERT_CASTBAR            = 0x00000020, // NYI; will cost me some sanity it seems
    SPELL_ATTR0_CU_LOW_TIME_TREAT_AS_INSTANT =
        0x00000040, // If cast time <= 250ms, changes tooltip line responsible to "Instant"
    SPELL_ATTR0_CU_LOW_TIME_FORCE_HIDE_CASTBAR  = 0x00000080, // If cast time <= 250ms, does not display cast bar
    SPELL_ATTR0_CU_LOW_CAST_TIME_DONT_INTERRUPT = 0x00000100, // If cast time <= 250ms, does not interrupt
};
