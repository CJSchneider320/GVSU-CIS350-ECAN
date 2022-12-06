#include <iostream>
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
    void run(World& ecs) {
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
                        gamelog.printlog("You pull the lever.");
                        toggle_connections(ecs, lever.first);
                    } else {
                        lever.second.active = true;
                        lever_render.glyph = LEVER_ON;
                        gamelog.printlog("You pull the lever.");
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
        for (auto connection : connections.targets) {
            for (auto& pos : positions) {
                if (level.position_to_index(pos.second.x, pos.second.y) == connection) {
                    auto& door = ecs.get_component<Door>(pos.first);
                    auto& door_render = ecs.get_component<Renderable>(pos.first);
                    if (door.d_status) {
                        door.d_status = false;
                        door_render.glyph = DOOR;
                        level.m_blocked_tiles[connection] = true;
                        gamelog.printlog("You hear a door slam shut.");
                    } else {
                        door.d_status = true;
                        door_render.glyph = LEFT_OPEN_DOOR;
                        level.m_blocked_tiles[connection] = false;
                        gamelog.printlog("You hear a door scrape open.");
                    }
                }
            }
        }
    }
};
