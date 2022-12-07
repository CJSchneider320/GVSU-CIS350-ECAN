#ifndef PLAYER_H_
#define PLAYER_H_

#include <ncurses.h>

#include "map.h"
#include "run_state.h"
#include "world.h"
#include "game_log.h"

extern GameLog gamelog;

class Player {
public:
    static RunState kill_player () {
        gamelog.printlog("You have died. ");
        gamelog.printlog("You hear a voice:");
        gamelog.printlog("\"You still have much to explore.\", you hear.");
        gamelog.printlog("You feel a rush of astral wind as you're taken to the beginning of the floor.");
        gamelog.printlog("The voice whispers once more, \"Avoid your folley that led to your demise.\".");
        return RunState::PreRun;
    }

    static void try_move_player(int delta_y, int delta_x, Entity player, Map& level, World& ecs) {
        auto& player_pos = ecs.get_component<Position>(player);

        int destination = level.position_to_index(player_pos.x + delta_x, player_pos.y + delta_y);
        ecs.add_component(player, AttemptedMove {destination});
        // Check if player is attempting to move outside the window
        if (player_pos.x + delta_x > level.m_width
                || player_pos.x + delta_x < 0
                || player_pos.y + delta_y > level.m_height
                || player_pos.y + delta_y < 0)
        {
            return;
        }

        // Create a destination and check if it's blocked
        if (!level.m_blocked_tiles[destination]) {
            // Update the player position
            auto new_player_pos = level.index_to_position(destination);
            level.m_tile_contents[level.position_to_index(player_pos.x, player_pos.y)].erase(player);
            player_pos.x = new_player_pos.x;
            player_pos.y = new_player_pos.y;
            level.m_tile_contents[level.position_to_index(player_pos.x, player_pos.y)].insert(player);
            auto new_tile_contents = level.m_tile_contents[destination];
            // Check for spikes
            auto& spikes = ecs.get_component_map<Spike>()->component_map;
            for (auto& spike : spikes) {
                for (auto content : new_tile_contents) {
                    if (spike.first == content) {
                        gamelog.printlog("You step on a spike!");
                        auto& c_spike = ecs.get_component<Spike>(spike.first);
                        c_spike.is_stood_on = true;
                    }
                }
            }
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
            case ' ':
            {
                auto& player_pos = ecs.get_component<Position>(player);
                auto tile_contents = level.m_tile_contents[level.position_to_index(player_pos.x, player_pos.y)];
                auto& interactables = ecs.get_component_map<Interactable>()->component_map;
                if (!tile_contents.empty()) {
                    for (auto interactable : interactables) {
                        auto& position = ecs.get_component<Position>(interactable.first);
                        if (level.position_to_index(player_pos.x, player_pos.y) == level.position_to_index(position.x, position.y)) {
                            ecs.add_component(player, WantsToInteract { interactable.first });
                        }
                    }
                    auto& stairs = ecs.get_component_map<Stairs>()->component_map;
                    if(!stairs.empty()) {
                        for (auto stair : stairs) {
                            auto& position = ecs.get_component<Position>(stair.first);
                            if (stair.second.is_exit
                                && level.position_to_index(player_pos.x, player_pos.y) == level.position_to_index(position.x, position.y)) {
                                level.m_previous_level = level.m_current_level;
                                level.m_current_level += 1;
                                gamelog.printlog("You ascend the staircase.");
                                return RunState::PreRun;
                            }
                        }
                    }
                    auto& chests = ecs.get_component_map<Chest>()->component_map;
                    for (auto& chest : chests) {
                        auto& chest_position = ecs.get_component<Position>(chest.first);
                        if (level.position_to_index(chest_position.x, chest_position.y)
                            == level.position_to_index(player_pos.x, player_pos.y)) {
                            auto& chest_component = ecs.get_component<Chest>(chest.first);
                            if (!chest_component.opened) {
                                auto& coinpurse = ecs.get_component<Coinpurse>(player);
                                coinpurse.coins += chest_component.gold;
                                chest_component.opened = true;
                                gamelog.printlog(std::string("You find " + std::to_string(chest_component.gold) + " coins in the chest.").c_str());
                                gamelog.printlog("You put them in your coinpurse.");
                            } else {
                                gamelog.printlog("The chest is empty.");
                            }
                        }
                    }
                }
                return RunState::PlayerTurn;
            }
            case 'g':
            {
                auto& coinpurse = ecs.get_component<Coinpurse>(player);
                gamelog.printlog(std::string("You have " + std::to_string(coinpurse.coins) + " gold coins.").c_str());
                return RunState::PlayerInput;
            }
            case 'q':
                return RunState::Exit;
            default:
                return RunState::PlayerInput;
        }
    }
};

#endif
