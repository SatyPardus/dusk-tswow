#include "MovementExtensions.h"
#include "Character/CharacterDefines.h"
#include "Unit/UnitExtensions.h"
#include "Logger.h"

void MovementExtensions::Apply() {
    Util::OverwriteUInt32AtAddress(0x6EFE8A, Util::CalculateAddress(reinterpret_cast<uint32_t>(&SetFacingEx), 0x6EFE8E));
    //
    Util::OverwriteUInt32AtAddress(0x6EFD12, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6EFD16));
    Util::OverwriteUInt32AtAddress(0x6EFD3B, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6EFD3F));
    Util::OverwriteUInt32AtAddress(0x6EFD88, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6EFD8C));
    Util::OverwriteUInt32AtAddress(0x6F1041, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6F1045));
    // Not sure if this is really needed but w/e
    Util::OverwriteUInt32AtAddress(0x6E9992, Util::CalculateAddress(reinterpret_cast<uint32_t>(&OnPitchStopEx), 0x6E9996));
    Util::OverwriteUInt32AtAddress(0x6EFDC6, Util::CalculateAddress(reinterpret_cast<uint32_t>(&OnPitchStopEx), 0x6EFDCA));
    Util::OverwriteUInt32AtAddress(0x6F10AA, Util::CalculateAddress(reinterpret_cast<uint32_t>(&OnPitchStopEx), 0x6F10AE));
}

bool MovementExtensions::CanPlayerGlide() {
    CGPlayer* activePlayer = reinterpret_cast<CGPlayer*>(ClntObjMgr::ObjectPtr(ClntObjMgr::GetActivePlayer(), TYPEMASK_PLAYER));

    return UnitExtensions::HasAuraByTypeId(&activePlayer->unitBase, SPELL_AURA_CAN_GLIDE);
}

void __fastcall MovementExtensions::SetFacingEx(CMovement* _this, uint32_t unused, float yaw) {
    float diff = 9.5367432e-7;
    bool canUpdateDirection = CanPlayerGlide();
    bool isFalling = _this->movementFlags & MOVEMENTFLAG_FALLING;

    if (fabs(yaw - _this->orientation) >= diff)
        _this->orientation = yaw;

    if (!isFalling || canUpdateDirection)
        CMovement_C::UpdatePositionFacingPitchAnchors(_this, canUpdateDirection);

    _this->movementFlags &= 0xFFFFFFCF;
}

// Aleist3r: refer to 0x988DF0
void __fastcall MovementExtensions::StartTurnEx(CMovement* _this, uint32_t unused, bool isLeft) {
    bool isFalling = _this->movementFlags & MOVEMENTFLAG_FALLING;
    bool canUpdateDirection = CanPlayerGlide();

    _this->movementFlags = (_this->movementFlags & 0xFFFFFFCF) | (isLeft ? MOVEMENTFLAG_LEFT : MOVEMENTFLAG_RIGHT);
    _this->movementFlags2 &= ~MOVEMENTFLAG2_INTERPOLATED_TURNING;
    _this->someX = _this->position.x;
    _this->someY = _this->position.y;
    _this->someZ = _this->position.z;
    _this->someO = _this->orientation;
    _this->somePitch = _this->pitch;
    _this->padding60 = 0.0f;

    if (isFalling && !canUpdateDirection)
        return;

    CMovement_C::sub_987E30(_this);

    if (_this->movementFlags & (MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD) && _this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
        // Diagonal movement (forward/backward + strafe)
        const float sin45 = 0.70710677f; // sin(45 degrees)

        if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
            _this->cosAngle = -_this->cosAngle;
            _this->sinAngle = -_this->sinAngle;
            _this->padding6C = -_this->padding6C;
            _this->someCos = -_this->someCos;
            _this->someSin = -_this->someSin;
        }

        std::swap(_this->someCos, _this->someSin);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->someCos = -_this->someCos;
        else
            _this->someSin = -_this->someCos;

        _this->cosAngle += _this->someCos;
        _this->sinAngle += _this->someSin;
        _this->someCos += _this->someCos;
        _this->someSin += _this->someSin;
        _this->cosAngle *= sin45;
        _this->sinAngle *= sin45;
        _this->padding6C *= sin45;
        _this->someCos *= sin45;
        _this->someSin *= sin45;
    }
    else if (_this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
        // Strafe-only movement
        std::swap(_this->someCos, _this->someSin);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->someCos = -_this->someCos;
        else
            _this->someSin = -_this->someCos;

        _this->cosAngle = _this->someCos;
        _this->sinAngle = _this->someSin;
        _this->padding6C = 0.0f;
    }
    else if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
        // Backward-only movement
        _this->cosAngle = -_this->cosAngle;
        _this->sinAngle = -_this->sinAngle;
        _this->padding6C = -_this->padding6C;
        _this->someCos = -_this->someCos;
        _this->someSin = -_this->someSin;
    }
}

// Aleist3r: refer to 0x989010
bool MovementExtensions::OnPitchStopEx(CMovement* _this, uint32_t unused) {
    bool isFalling = _this->movementFlags & MOVEMENTFLAG_FALLING;
    bool canUpdateDirection = CanPlayerGlide();

    if (!(_this->movementFlags & (MOVEMENTFLAG_LEFT | MOVEMENTFLAG_RIGHT)))
        return false;

    _this->someX = _this->position.x;
    _this->someY = _this->position.y;
    _this->someZ = _this->position.z;
    _this->someO = _this->orientation;
    _this->somePitch = _this->pitch;
    _this->padding60 = 0.0;
    _this->movementFlags &= 0xFFFFFFCF;

    if (isFalling && !canUpdateDirection)
        return true;

    CMovement_C::sub_987E30(_this);

    // Aleist3r: seems to essentially refactor to the same code tester did, just with additional `return true;`
    if (_this->movementFlags & (MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD) && _this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
        // Diagonal movement (forward/backward + strafe)
        const float sin45 = 0.70710677f; // sin(45 degrees)

        if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
            _this->cosAngle = -_this->cosAngle;
            _this->sinAngle = -_this->sinAngle;
            _this->padding6C = -_this->padding6C;
            _this->someCos = -_this->someCos;
            _this->someSin = -_this->someSin;
        }

        std::swap(_this->someCos, _this->someSin);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->someCos = -_this->someCos;
        else
            _this->someSin = -_this->someCos;

        _this->cosAngle += _this->someCos;
        _this->sinAngle += _this->someSin;
        _this->someCos += _this->someCos;
        _this->someSin += _this->someSin;
        _this->cosAngle *= sin45;
        _this->sinAngle *= sin45;
        _this->padding6C *= sin45;
        _this->someCos *= sin45;
        _this->someSin *= sin45;
    }
    else if (_this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
        // Strafe-only movement
        std::swap(_this->someCos, _this->someSin);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->someCos = -_this->someCos;
        else
            _this->someSin = -_this->someCos;

        _this->cosAngle = _this->someCos;
        _this->sinAngle = _this->someSin;
        _this->padding6C = 0.0f;
    }
    else if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
        // Backward-only movement
        _this->cosAngle = -_this->cosAngle;
        _this->sinAngle = -_this->sinAngle;
        _this->padding6C = -_this->padding6C;
        _this->someCos = -_this->someCos;
        _this->someSin = -_this->someSin;
    }

    return true;
}
