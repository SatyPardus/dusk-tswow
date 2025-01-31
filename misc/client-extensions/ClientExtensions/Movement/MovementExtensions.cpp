#include "MovementExtensions.h"
#include "Unit/UnitExtensions.h"

// Aleist3r: this is ugly but unless you explain to me how to calculate jumps when I don't know initial address in the function
// so deal with it :P
static void __declspec(naked) CMovement__StartTurnBlock() {
    __asm {
        call MovementExtensions::CanPlayerGlide;
        cmp eax, 1;
        //jz 0x988E4E;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        // jmp 0x988FF8
        nop;
        nop;
        nop;
        nop;
        nop;
    }
}

// this is even uglier with that int 3, cba to search how to change this behavior
// but normally this and above get consolidated into the same function upon compilation
// if both of them are identical
static void __declspec(naked) CMovement__OnPitchStop_0Block() {
    __asm {
        call MovementExtensions::CanPlayerGlide;
        cmp eax, 1;
        // jz 0x989059;
        int 3;
        nop;
        nop;
        nop;
        nop;
        nop;
        // jmp 0x989203
        nop;
        nop;
        nop;
        nop;
        nop;
    }
}

void __fastcall MovementExtensions::SetFacing(void* _this, uint32_t unused, float yaw) {
    uintptr_t* thisPtr = reinterpret_cast<uintptr_t*>(_this);
    float amount = *reinterpret_cast<float*>(0x9F1224);
    float currentOrientation = *reinterpret_cast<float*>(thisPtr + 8);
    bool canUpdateDirection = false;
    bool isFalling = (*reinterpret_cast<uint32_t*>(thisPtr + 17)) & 0x1000;

    if (fabs(yaw - currentOrientation) >= amount)
        *reinterpret_cast<float*>(thisPtr + 8) = yaw;

    if (CanPlayerGlide())
        canUpdateDirection = true;

    if (!isFalling || (isFalling && canUpdateDirection))
        CMovement__UpdatePositionFacingPitchAnchors(_this, canUpdateDirection);

    *reinterpret_cast<uint32_t*>(thisPtr + 17) &= 0xFFFFFFCF;
}

bool MovementExtensions::CanPlayerGlide() {
    uint64_t activePlayer = ClntObjMgrGetActivePlayer();
    void* activePlayerPtr = ClntObjMgrObjectPtr(activePlayer, TYPEMASK_PLAYER);
    bool result = false;

    if (UnitExtensions::HasAuraByTypeId(activePlayerPtr, SPELL_AURA_CAN_GLIDE))
        result = true;

    return result;
}

void MovementExtensions::Apply() {
    DWORD flOldProtect = 0;

    OverwriteUInt32AtAddress(0x6EFE8A, CalculateAddress(reinterpret_cast<uint32_t>(&SetFacing), 0x6EFE8E));

    /*// CMovement__StartTurn() jump address
    OverwriteUInt32AtAddress(0x988E4A, CalculateAddress(reinterpret_cast<uint32_t>(&CMovement__StartTurnBlock), 0x988E4E));
    // update CMovement__StartTurnBlock(), jz
    uint32_t functAddress = reinterpret_cast<uint32_t>(&CMovement__StartTurnBlock);
    VirtualProtect((LPVOID)(functAddress + 8), 0x2, PAGE_EXECUTE_READWRITE, &flOldProtect);
    *reinterpret_cast<uint8_t*>(functAddress + 8) = 0x0F;
    *reinterpret_cast<uint8_t*>(functAddress + 9) = 0x84;
    VirtualProtect((LPVOID)(functAddress + 8), 0x2, flOldProtect, &flOldProtect);
    OverwriteUInt32AtAddress(functAddress + 10, CalculateAddress(functAddress + 14, 0x988E4E, true));
    // jmp
    VirtualProtect((LPVOID)(functAddress + 14), 0x1, PAGE_EXECUTE_READWRITE, &flOldProtect);
    *reinterpret_cast<uint8_t*>(functAddress + 14) = 0xE9;
    VirtualProtect((LPVOID)(functAddress + 14), 0x1, flOldProtect, &flOldProtect);
    OverwriteUInt32AtAddress(functAddress + 15, CalculateAddress(functAddress + 19, 0x988FF8, true));

    // CMovement__OnPitchStop_0() jump address
    OverwriteUInt32AtAddress(0x989055, CalculateAddress(reinterpret_cast<uint32_t>(&CMovement__OnPitchStop_0Block), 0x989059));
    // update CMovement__StartTurnBlock(), jz
    functAddress = reinterpret_cast<uint32_t>(&CMovement__OnPitchStop_0Block);
    VirtualProtect((LPVOID)(functAddress + 8), 0x2, PAGE_EXECUTE_READWRITE, &flOldProtect);
    *reinterpret_cast<uint8_t*>(functAddress + 8) = 0x0F;
    *reinterpret_cast<uint8_t*>(functAddress + 9) = 0x85;
    VirtualProtect((LPVOID)(functAddress + 8), 0x2, flOldProtect, &flOldProtect);
    OverwriteUInt32AtAddress(functAddress + 10, CalculateAddress(functAddress + 14, 0x989059, true));
    // jmp
    VirtualProtect((LPVOID)(functAddress + 14), 0x1, PAGE_EXECUTE_READWRITE, &flOldProtect);
    *reinterpret_cast<uint8_t*>(functAddress + 14) = 0xE9;
    VirtualProtect((LPVOID)(functAddress + 14), 0x1, flOldProtect, &flOldProtect);
    OverwriteUInt32AtAddress(functAddress + 15, CalculateAddress(functAddress + 19, 0x989203, true));*/
}
