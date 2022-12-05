#ifndef COMPONENTS_H_
#define COMPONENTS_H_
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

struct CPlayer {};

struct Connection {
    int source;
    int target;
};

struct Door {
    bool d_status;
    // true = open
    // false = closed
};

#endif
