#ifndef PLAYER_H_
#define PLAYER_H_

#include <ncurses.h>

#include "map.h"
#include "run_state.h"
#include "world.h"

class Player {
public:
    static void try_move_player(int delta_y, int delta_x, Entity player, Map& level, World& ecs) {
        auto& player_pos = ecs.get_component<Position>(player);

        // Check if player is attempting to move outside the window
        if (player_pos.x + delta_x > level.m_width
                || player_pos.x + delta_x < 0
                || player_pos.y + delta_y > level.m_height
                || player_pos.y + delta_y < 0)
        {
            return;
        }

        // Create a destination and check if it's blocked
        int destination = level.position_to_index(player_pos.x + delta_x, player_pos.y + delta_y);
        if (!level.m_blocked_tiles[destination]) {
            // Update the player position
            auto new_player_pos = level.index_to_positon(destination);
            player_pos.x = new_player_pos.x;
            player_pos.y = new_player_pos.y;
        }
    }

    static RunState player_input(Entity player, Map& level, World& ecs) {
        int player_input = getch();
        switch (player_input) {
            case 'w':
            case 'k':
            case KEY_UP:
                try_move_player(-1, 0, player, level, ecs);
                return RunState::PlayerTurn;
            case 's':
            case 'j':
            case KEY_DOWN:
                try_move_player(1, 0, player, level, ecs);
                return RunState::PlayerTurn;
            case 'a':
            case 'h':
            case KEY_LEFT:
                try_move_player(0, -1, player, level, ecs);
                return RunState::PlayerTurn;
            case 'd':
            case 'l':
            case KEY_RIGHT:
                try_move_player(0, 1, player, level, ecs);
                return RunState::PlayerTurn;
            case 'q':
                return RunState::Exit;
            default:
                return RunState::PlayerInput;
        }
    }
};

#endif
