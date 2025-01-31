#pragma once

#include "ClientDB.h"
#include "Character/CharacterFixes.h"
#include "Movement/MovementExtensions.h"
#include "Tooltip/SpellTooltipExtensions.h"

class ClientExtensions {
private:
    static void initialize();
    friend class Main;
};
