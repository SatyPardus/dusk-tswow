#pragma once

#include "C3Vector.h"

struct MovementInfo
{
    uint32_t padding[2];
    uint64_t moverGUID;
    C3Vector position;
    float padding1C;
    float orientation;
    float pitch;
    uint32_t padding28[7];
    uint32_t movementFlags;
    uint32_t movementFlags2;
    uint32_t padding4C[65];
    // TODO: add rest, probably when needed
};
