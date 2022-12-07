#ifndef INTERACTION_SYSTEM_H_
#define INTERACTION_SYSTEM_H_
#include <iostream>
#include <ncurses.h>

#include "world.h"
#include "system.h"
#include "components.h"
#include "chars.h"
#include "colordata.h"
#include "map.h"
#include "game_log.h"

extern Map level;
extern GameLog gamelog;

class Interaction : public System {
public:
    void run(World& ecs) override {
        for (Entity entity : entities) {
            auto& wants_interact = ecs.get_component<WantsToInteract>(entity);
            auto& position = ecs.get_component<Position>(wants_interact.target);
            auto& levers = ecs.get_component_map<Lever>()->component_map;
            for (auto& lever : levers) {
                if (lever.first == wants_interact.target) {
                    auto& lever_render = ecs.get_component<Renderable>(lever.first);
                    if (lever.second.active) {
                        lever.second.active = false;
                        lever_render.glyph = LEVER_OFF;
                        gamelog.printlog("You try to pull the lever.");
                        toggle_connections(ecs, lever.first);
                    } else {
                        lever.second.active = true;
                        lever_render.glyph = LEVER_ON;
                        gamelog.printlog("You try to pull the lever.");
                        toggle_connections(ecs, lever.first);
                    }
                }
            }
            ecs.remove_component<WantsToInteract>(entity);
        }
    }
    
    void toggle_connections(World& ecs, Entity entity) {
        auto& lever = ecs.get_component<Lever>(entity);
        auto& connections = ecs.get_component<Connection>(entity);
        auto& positions = ecs.get_component_map<Position>()->component_map;
        auto& doors = ecs.get_component_map<Door>()->component_map;
        auto& connections_map = ecs.get_component_map<Connection>()->component_map;

        for (auto& connection : connections.targets) {
            for (auto& door : doors) {
                auto& door_pos = ecs.get_component<Position>(door.first);
                if (level.position_to_index(door_pos.x, door_pos.y) == connection) {
                    for (auto tile_content : level.m_tile_contents[level.position_to_index(door_pos.x, door_pos.y)]) {
                        if (tile_content != door.first) {
                            gamelog.printlog("You can't seem to move the lever.");
                            gamelog.printlog("Something must be preventing you from flipping it.");
                            return;
                        }
                    }
                }
            }
        }

        for (auto connection : connections.targets) {
            for (auto& door : doors) {
                auto& door_pos = ecs.get_component<Position>(door.first);
                if (level.position_to_index(door_pos.x, door_pos.y) == connection) {
                    auto& c_door = ecs.get_component<Door>(door.first);
                    auto& door_render = ecs.get_component<Renderable>(door.first);
                    if (c_door.d_status) {
                        c_door.d_status = false;
                        door_render.glyph = DOOR;
                        level.m_blocked_tiles[connection] = true;
                        gamelog.printlog("You hear a door slam shut.");
                    } else {
                        c_door.d_status = true;
                        door_render.glyph = LEFT_OPEN_DOOR;
                        level.m_blocked_tiles[connection] = false;
                        gamelog.printlog("You hear a door scrape open.");
                    }
                }
            }
        }
    }
};

#endif
