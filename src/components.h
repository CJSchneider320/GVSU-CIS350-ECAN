#include <string>
#include "colordata.h"

struct Position {
    int x;
    int y;
};

struct Renderable {
    std::string glyph;
    int symbol_color;
};
