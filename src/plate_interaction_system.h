#ifndef PLATE_INTERACTION_SYSTEM_H_
#define PLATE_INTERACTION_SYSTEM_H_

#include "system.h"
#include "components.h"
#include "world.h"
#include "map.h"
#include "game_log.h"

extern Map level;
extern GameLog gamelog;


class PlateInteractionSystem : public System {
    void run(World& ecs) override {
        bool entity_on_plate;

        for (Entity entity : entities) {
            entity_on_plate = false;
            auto& plate = ecs.get_component<PressurePlate>(entity);
            auto& entity_pos = ecs.get_component<Position>(entity);
            auto& ambulates = ecs.get_component_map<Ambulates>()->component_map;

            for (auto ambulator : ambulates) {
                auto& ambulator_pos = ecs.get_component<Position>(ambulator.first);
                if (level.position_to_index(entity_pos.x, entity_pos.y) == level.position_to_index(ambulator_pos.x, ambulator_pos.y)) {
                    entity_on_plate = true;
                    break;
                }

            }
            if (entity_on_plate) {
                if (!plate.is_stood_on) {
                    plate.is_stood_on = true;
                    toggle_connections(ecs, entity);
                }
            } else {
                if (plate.is_stood_on) {
                    plate.is_stood_on = false;
                    toggle_connections(ecs, entity);
                }
            }
        }
    }

    void toggle_connections(World& ecs, Entity entity) {
        auto& plate = ecs.get_component<PressurePlate>(entity);
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

#endif
