#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <string>
#include <vector>
#include "EcsConstants.h"
#include "colordata.h"

struct Position {
    int x;
    int y;
};

struct Renderable {
    std::string glyph;
    int symbol_color;
    int render_order;
};

struct CPlayer {};

struct Connection {
    std::vector<int> targets;
};

struct Door {
    bool d_status;
    // true = open
    // false = closed
};

struct Lever {
    bool active;
};

struct Interactable {};

struct WantsToInteract {
    Entity target;
};

struct Stairs {
    bool is_exit;
};

struct Chest {
    bool opened;
    int gold;
};

struct PressurePlate {
    bool is_stood_on;
};

struct Robot {};

struct Ambulates {};

struct AttemptedMove {
    int destination;
};

struct Spike {
    bool is_stood_on;
};

struct Dead {};

struct Coinpurse {
    int coins;
};

#endif
