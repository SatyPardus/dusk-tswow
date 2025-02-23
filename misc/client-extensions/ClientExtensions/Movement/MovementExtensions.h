#pragma once

#include "SharedDefines.h"

class MovementExtensions {
private:
    static void Apply();

    static bool CanPlayerGlide();

    static void __fastcall SetFacingEx(CMovement* _this, uint32_t unused, float yaw);
    static void __fastcall StartTurnEx(CMovement* _this, uint32_t unused, bool isLeft);
    friend class ClientExtensions;
};
