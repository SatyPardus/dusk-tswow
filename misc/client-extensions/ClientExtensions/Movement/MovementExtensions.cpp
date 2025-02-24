#include "MovementExtensions.h"
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
    Util::OverwriteUInt32AtAddress(0x6E9992, Util::CalculateAddress(reinterpret_cast<uint32_t>(&OnPitchStop), 0x6E9996));
    Util::OverwriteUInt32AtAddress(0x6EFDC6, Util::CalculateAddress(reinterpret_cast<uint32_t>(&OnPitchStop), 0x6EFDCA));
    Util::OverwriteUInt32AtAddress(0x6F10AA, Util::CalculateAddress(reinterpret_cast<uint32_t>(&OnPitchStop), 0x6F10AE));
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
    _this->padding40[0] = _this->position.x;
    _this->padding40[1] = _this->position.y;
    _this->padding40[2] = _this->position.z;
    _this->padding40[3] = _this->orientation;
    _this->padding40[4] = _this->pitch;
    _this->padding40[5] = 0;

    if (isFalling && !canUpdateDirection)
        return;

    CMovement_C::sub_987E30(_this);

    if (_this->movementFlags & (MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD) && _this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
        // Diagonal movement (forward/backward + strafe)
        const float sin45 = 0.70710677f; // sin(45 degrees)

        if (_this->movementFlags & MOVEMENTFLAG_BACKWARD)
            for (int i = 6; i <= 10; ++i) 
                _this->padding40[i] = -_this->padding40[i];

        std::swap(_this->padding40[9], _this->padding40[10]);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->padding40[9] = -_this->padding40[9];
        else
            _this->padding40[10] = -_this->padding40[10];

        for (int i = 6; i <= 10; ++i)
            _this->padding40[i] *= sin45;
    }
    else if (_this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
        // Strafe-only movement
        std::swap(_this->padding40[9], _this->padding40[10]);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->padding40[9] = -_this->padding40[9];
        else
            _this->padding40[10] = -_this->padding40[10];

        _this->padding40[6] = _this->padding40[9];
        _this->padding40[7] = _this->padding40[10];
        _this->padding40[8] = 0.0f;
    }
    else if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
        // Backward-only movement
        for (int i = 6; i <= 10; ++i) 
            _this->padding40[i] = -_this->padding40[i];
    }
}

// Aleist3r: refer to 0x989010
bool MovementExtensions::OnPitchStop(CMovement* _this, uint32_t unused) {
    bool isFalling = _this->movementFlags & MOVEMENTFLAG_FALLING;
    bool canUpdateDirection = CanPlayerGlide();

    if (!(_this->movementFlags & (MOVEMENTFLAG_LEFT | MOVEMENTFLAG_RIGHT)))
        return false;

    _this->padding40[0] = _this->position.x;
    _this->padding40[1] = _this->position.y;
    _this->padding40[2] = _this->position.z;
    _this->padding40[3] = _this->orientation;
    _this->padding40[4] = _this->pitch;
    _this->padding40[5] = 0.0;
    _this->movementFlags &= 0xFFFFFFCF;

    if (!isFalling || (isFalling && canUpdateDirection)) {
        CMovement_C::sub_987E30(_this);

        if (_this->movementFlags & (MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD)) {
            if (_this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
                const float sin45 = 0.70710677;
                float padding0x64 = _this->padding40[6];
                float padding0x68 = _this->padding40[7];
                float padding0x6C = _this->padding40[8];
                float padding0x70 = _this->padding40[9];
                float padding0x74 = _this->padding40[10];

                if (_this->movementFlags & MOVEMENTFLAG_BACKWARD)
                {
                    padding0x64 = -_this->padding40[6];
                    padding0x68 = -_this->padding40[7];
                    padding0x6C = -_this->padding40[8];
                    padding0x70 = -_this->padding40[9];
                    padding0x74 = -_this->padding40[10];
                }

                std::swap(_this->padding40[9], _this->padding40[10]);

                if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
                    _this->padding40[9] = -_this->padding40[9];
                else
                    _this->padding40[10] = -_this->padding40[10];

                //float v9 = _this->padding40[10];
                //float v22 = _this->padding40[9] + padding0x64;
                //_this->padding40[6] = v22;
                //float v25 = v9 + padding0x68;
                //_this->padding40[7] = v25;
                //_this->padding40[8] = padding0x6C;
                //_this->padding40[9] = _this->padding40[9] + padding0x70;
                //_this->padding40[10] = _this->padding40[10] + padding0x74;
                //_this->padding40[6] = _this->padding40[6] * sin45;
                //_this->padding40[7] = _this->padding40[7] * sin45;
                //_this->padding40[8] = _this->padding40[8] * sin45;
                //_this->padding40[9] = _this->padding40[9] * sin45;
                //_this->padding40[10] = _this->padding40[10] * sin45;

                _this->padding40[6] = (_this->padding40[9] + padding0x64) * sin45;
                _this->padding40[7] = (_this->padding40[10] + padding0x68) * sin45;
                _this->padding40[8] = padding0x6C * sin45;
                _this->padding40[9] = (_this->padding40[9] + padding0x70) * sin45;
                _this->padding40[10] = (_this->padding40[10] + padding0x74) * sin45;

                goto LABEL_19;
            }
LABEL_17:
            if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
                //float v15 = -_this->padding40[6];
                //float v18 = -_this->padding40[7];
                //float v12 = _this->padding40[8];
                //_this->padding40[6] = v15;
                //_this->padding40[7] = v18;
                //float v20 = -v12;
                //float v26 = -_this->padding40[9];
                //float v13 = _this->padding40[10];
                //_this->padding40[9] = v26;
                //float v29 = -v13;
                //_this->padding40[10] = v29;

                _this->padding40[6] = -_this->padding40[6];
                _this->padding40[7] = -_this->padding40[7];
                _this->padding40[8] = -_this->padding40[8];
                _this->padding40[9] = -_this->padding40[9];
                _this->padding40[10] = -_this->padding40[10];
            }
            goto LABEL_19;
        }
        if (!(_this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)))
            goto LABEL_17;

        std::swap(_this->padding40[9], _this->padding40[10]);

        if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
            _this->padding40[9] = -_this->padding40[9];
        else
            _this->padding40[10] = -_this->padding40[10];

        _this->padding40[6] = _this->padding40[9];
        _this->padding40[7] = _this->padding40[10];
        _this->padding40[8] = 0.0f;
    }
LABEL_19:
    return true;
}
