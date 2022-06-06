#pragma once

#include "globals.hpp"

struct screenPoint {
    u16 x;
    u16 y;
    u16 z;
};

struct screenTri {
    screenPoint p1;
    screenPoint p2;
    screenPoint p3;
};

void renderFrame(u8* screenData);
