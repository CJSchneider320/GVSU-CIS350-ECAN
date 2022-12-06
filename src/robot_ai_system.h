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

        // Get player positions
        for (auto player : players) {
            auto player_pos = ecs.get_component<Position>(player.first);

            if (current_player_pos.x == 0 && current_player_pos.y == 0
                && previous_player_pos.x == 0 && previous_player_pos.y == 0) {
                current_player_pos.x = player_pos.x;
                current_player_pos.y = player_pos.y;
                previous_player_pos.x = player_pos.x;
                previous_player_pos.y = player_pos.y;
            } else {
                previous_player_pos.x = current_player_pos.x;
                previous_player_pos.y = current_player_pos.y;
                current_player_pos.x = player_pos.x;
                current_player_pos.y = player_pos.y;
            }
        }
        
        if (current_player_pos.x != previous_player_pos.x
            || current_player_pos.y != previous_player_pos.y) {
            for (Entity entity : entities) {
                auto& position = ecs.get_component<Position>(entity);
                int delta_x = current_player_pos.x - previous_player_pos.x;
                int delta_y = current_player_pos.y - previous_player_pos.y;
                
                int destination = level.position_to_index(position.x + delta_x, position.y + delta_y);
                if (!level.m_blocked_tiles[destination]) {
                    auto new_entity_pos = level.index_to_position(destination);
                    level.m_tile_contents[level.position_to_index(position.x, position.y)].pop_back();
                    level.m_blocked_tiles[level.position_to_index(position.x, position.y)] = false;
                    position.x = new_entity_pos.x;
                    position.y = new_entity_pos.y;
                    level.m_tile_contents[destination].push_back(entity);
                    level.m_blocked_tiles[destination] = true;
                }
            }
        }
    }
};

#endif
