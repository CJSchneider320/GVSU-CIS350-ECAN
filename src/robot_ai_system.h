#ifndef ROBOT_AI_SYSTEM_H_
#define ROBOT_AI_SYSTEM_H_

#include "system.h"
#include "components.h"
#include "map.h"

extern Map level;

class RobotAiSystem : public System {
    Position current_player_pos = Position {0, 0};
    Position previous_player_pos = Position {0, 0};
public:
    void run(World& ecs) {
        auto players = ecs.get_component_map<CPlayer>()->component_map;
        auto attempted_moves = ecs.get_component_map<AttemptedMove>()->component_map;

        // Get player positions
        for (auto player : players) {
            auto player_pos = ecs.get_component<Position>(player.first);

            if (current_player_pos.x == 0 && current_player_pos.y == 0
                && previous_player_pos.x == 0 && previous_player_pos.y == 0 || attempted_moves.empty()) {
                current_player_pos.x = player_pos.x;
                current_player_pos.y = player_pos.y;
                previous_player_pos.x = player_pos.x;
                previous_player_pos.y = player_pos.y;
            } else if (!attempted_moves.empty()) {
                for (auto attempted_move : attempted_moves) {
                    auto attempted_pos = level.index_to_position(attempted_move.second.destination);
                    previous_player_pos.x = current_player_pos.x;
                    previous_player_pos.y = current_player_pos.y;
                    current_player_pos.x = attempted_pos.x;
                    current_player_pos.y = attempted_pos.y;
                }
            }
        }
        
        if (current_player_pos.x != previous_player_pos.x
            || current_player_pos.y != previous_player_pos.y) {
            int delta_x = current_player_pos.x - previous_player_pos.x;
            int delta_y = current_player_pos.y - previous_player_pos.y;
            for (Entity entity : entities) {
                auto& position = ecs.get_component<Position>(entity);
                int destination = level.position_to_index(position.x + delta_x, position.y + delta_y);
                if (!level.m_blocked_tiles[destination]) {
                    auto new_entity_pos = level.index_to_position(destination);
                    level.m_tile_contents[level.position_to_index(position.x, position.y)].erase(entity);
                    level.m_blocked_tiles[level.position_to_index(position.x, position.y)] = false;
                    position.x = new_entity_pos.x;
                    position.y = new_entity_pos.y;
                    level.m_tile_contents[destination].insert(entity);
                    level.m_blocked_tiles[destination] = true;

                    auto new_tile_contents = level.m_tile_contents[destination];
                    // Check for spikes
                    auto& spikes = ecs.get_component_map<Spike>()->component_map;
                    for (auto& spike : spikes) {
                        for (auto content : new_tile_contents) {
                            if (spike.first == content) {
                                auto& c_spike = ecs.get_component<Spike>(spike.first);
                                c_spike.is_stood_on = true;
                            }
                        }
                    }
                }
            }
        }
        for (auto player : players) {
            if (!attempted_moves.empty()) {
                ecs.remove_component<AttemptedMove>(player.first);
            }
        }
    }
};

#endif
