#include "windows.h"
#include "ClientExtensions.h"
#include "CDBCMgr/CDBCMgr.h"
#include "ClientDetours.h"
#include "Logger.h"

void ClientExtensions::initialize() {
    CDBCMgr::Load();
    LOG_INFO << "Custom DBCs loaded";
    CharacterFixes::CharacterCreationFixes();
    LOG_INFO << "Character creation fixes applied";
    CharacterExtensions::Apply();
    LOG_INFO << "Character extensions applied";
    TooltipExtensions::Apply();
    LOG_INFO << "Tooltip extensions applied";
    MovementExtensions::Apply();
    LOG_INFO << "Movement extensions applied";
    MiscFixes::Apply();
    LOG_INFO << "Misc fixes applied";
}

void ClientExtensions::ResetCustomData() {
    CharacterExtensions::ResetCustomData();
}

CLIENT_DETOUR(OnHandleDisconnect, 0x4DA9D0, __cdecl, int, (int a1)) {
    ClientExtensions::ResetCustomData();

    return OnHandleDisconnect(a1);
}
