#pragma once
#ifndef INCLUDE_PHOENIX_COLOR_H
#define INCLUDE_PHOENIX_COLOR_H

#include <cstdint>

struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

const Color COLOR_WHITE = Color{255,255,255,255};
const Color COLOR_BLACK = Color{0,0,0,255};
const Color COLOR_RED = Color{255,0,0,255};
const Color COLOR_GREEN = Color{0,255,0,255};
const Color COLOR_BLUE = Color{0,0,255,255};
const Color COLOR_YELLOW = Color{255,255,0,255};
const Color COLOR_CYAN = Color{0,255,255,255};
const Color COLOR_MAGENTA = Color{255,0,255,255};
const Color COLOR_TRANSPARENT = Color{0,0,0,0};

#endif //INCLUDE_PHOENIX_COLOR_H
