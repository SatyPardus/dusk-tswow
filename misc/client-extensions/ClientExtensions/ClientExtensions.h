#pragma once

#include "Character/CharacterExtensions.h"
#include "Character/CharacterFixes.h"
#include "Misc/MiscFixes.h"
#include "Movement/MovementExtensions.h"
#include "Tooltip/SpellTooltipExtensions.h"
#include "World/WorldData.h"

class ClientExtensions {
public:
    static void ResetCustomData();
private:
    static void initialize();
    friend class Main;
};
