#pragma once
#include "SharedDefines.h"

CLIENT_FUNCTION(CMovement__UpdatePositionFacingPitchAnchors, 0x9881D0, __thiscall, void, (void*, bool))
CLIENT_FUNCTION(CMovement__SetFacing, 0x989B70, __thiscall, void, (void*, float))

static uint32_t doOnce = 0;

class MovementExtensions {
public:
    static void __fastcall SetFacing(void* _this, uint32_t unused, float yaw);
    static bool CanPlayerGlide();
private:
    // Aleist3r: instead of asm patching and getting cancer from it just straight rewrite
    // also, anyone looking for missing knowledge, to write __thiscall hook or whatever you use __fastcall
    // took me a bit to find exact info because ofc teh webz assumes you know everything :P
    // the main difference is __thiscall uses ecx as 1st arg, fastcall uses ecx and edx as 1st and 2nd args
    // that's where uint32_t unused comes from, to not get fucked by some bogus value
    static void Apply();
    friend class ClientExtensions;
};
