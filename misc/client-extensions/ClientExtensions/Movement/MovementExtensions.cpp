#include "MovementExtensions.h"

void MovementExtensions::Apply() {
    Util::OverwriteUInt32AtAddress(0x6EFE8A, Util::CalculateAddress(reinterpret_cast<uint32_t>(&SetFacingEx), 0x6EFE8E));
    //
    Util::OverwriteUInt32AtAddress(0x6EFD12, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6EFD16));
    Util::OverwriteUInt32AtAddress(0x6EFD3B, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6EFD3F));
    Util::OverwriteUInt32AtAddress(0x6EFD88, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6EFD8C));
    Util::OverwriteUInt32AtAddress(0x6F1041, Util::CalculateAddress(reinterpret_cast<uint32_t>(&StartTurnEx), 0x6F1045));
}

bool MovementExtensions::CanPlayerGlide() {
    bool result = false;

    return result;
}

void __fastcall MovementExtensions::SetFacingEx(CMovement* _this, uint32_t unused, float yaw) {
    float diff = 9.5367432e-7;
    bool canUpdateDirection = CanPlayerGlide();
    bool isFalling = _this->movementFlags & MOVEMENTFLAG_FALLING;

    if (fabs(yaw - _this->orientation) >= diff)
        _this->orientation = yaw;

    if (!isFalling || (isFalling && canUpdateDirection))
        CMovement_C::UpdatePositionFacingPitchAnchors(_this, canUpdateDirection);

    _this->movementFlags &= 0xFFFFFFCF;
}

// Aleist3r: refer to 0x988DF0
void __fastcall MovementExtensions::StartTurnEx(CMovement* _this, uint32_t unused, bool isLeft) {
    bool isFalling = _this->movementFlags & MOVEMENTFLAG_FALLING;
    bool canUpdateDirection = false;

    if (CanPlayerGlide())
        canUpdateDirection = true;

    if (isLeft)
        _this->movementFlags = _this->movementFlags & 0xFFFFFFCF | MOVEMENTFLAG_LEFT;
    else
        _this->movementFlags = _this->movementFlags & 0xFFFFFFCF | MOVEMENTFLAG_RIGHT;

    
    _this->movementFlags2 &= ~MOVEMENTFLAG2_INTERPOLATED_TURNING;
    _this->padding40[0] = _this->position.x;
    _this->padding40[1] = _this->position.y;
    _this->padding40[2] = _this->position.z;
    _this->padding40[3] = _this->orientation;
    _this->padding40[4] = _this->pitch;
    _this->padding40[5] = 0;

    if (!isFalling || (isFalling && canUpdateDirection)) {
        CMovement_C::sub_987E30(_this);

        if ((_this->movementFlags & (MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD)) && _this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
            float sin45 = 0.70710677;
            float padding0x64 = _this->padding40[6];
            float padding0x68 = _this->padding40[7];
            float padding0x6C = _this->padding40[8];
            float padding0x70 = _this->padding40[9];
            float padding0x74 = _this->padding40[10];

            if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
                padding0x64 = -_this->padding40[6];
                padding0x68 = -_this->padding40[7];
                padding0x6C = -_this->padding40[8];
                padding0x70 = -_this->padding40[9];
                padding0x74 = -_this->padding40[10];
            }

            float rev = _this->padding40[9];
            _this->padding40[9] = _this->padding40[10];
            _this->padding40[10] = rev;

            if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
                _this->padding40[9] = -_this->padding40[9];
            else
                _this->padding40[10] = -_this->padding40[10];

            //float v8 = _this->padding40[10];
            //float v22 = _this->padding40[9] + padding0x64;
            //_this->padding40[6] = v22;
            //float v25 = v8 + padding0x68;
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

            return;
        }
        else if (_this->movementFlags & (MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT)) {
            float rev = _this->padding40[9];
            _this->padding40[9] = _this->padding40[10];
            _this->padding40[10] = rev;

            if (_this->movementFlags & MOVEMENTFLAG_STRAFE_LEFT)
                _this->padding40[9] = -_this->padding40[9];
            else
                _this->padding40[10] = -_this->padding40[10];

            // Aleist3r: I know that commented out part is retaded, it's just a direct rewrite from shit IDA did, and then refactored
            //float v10 = _this->padding40[10];
            _this->padding40[6] = _this->padding40[9];
            //float v17 = v10;
            _this->padding40[7] = _this->padding40[10];
            _this->padding40[8] = 0.0;

            return;
        }

        if (_this->movementFlags & MOVEMENTFLAG_BACKWARD) {
            //float padding0x64 = -_this->padding40[6];
            //float padding0x68 = -_this->padding40[7];
            //float padding0x6C = _this->padding40[8];

            //_this->padding40[6] = padding0x64;
            //_this->padding40[7] = padding0x68;
            //float v20 = -padding0x6C;
            //_this->padding40[8] = v20;
            //float padding0x70 = -_this->padding40[9];
            //float padding0x74 = _this->padding40[10];
            //_this->padding40[9] = padding0x70;
            //float v29 = -padding0x74;
            //_this->padding40[10] = v29;

            _this->padding40[6] = -_this->padding40[6];
            _this->padding40[7] = -_this->padding40[7];
            _this->padding40[8] = -_this->padding40[8];
            _this->padding40[9] = -_this->padding40[9];
            _this->padding40[10] = -_this->padding40[10];
        }
    }
}
