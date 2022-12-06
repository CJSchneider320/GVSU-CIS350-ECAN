//#include "system.h"
//#include "components.h"
//#include "world.h"
//#include "map.h"
//#include "chars.h"
//
//// Global Map
//extern Map level;
//
//class ToggleConnectionsSystem : public System {
//    void run(World& ecs) override {
//        for (Entity entity : entities) {
//            auto& lever = ecs.get_component<Lever>(entity);
//            auto& connections = ecs.get_component<Connection>(entity);
//            auto& positions = ecs.get_component_map<Position>()->component_map;
//            for (auto connection : connections.targets) {
//                for (auto& pos : positions) {
//                    if (level.position_to_index(pos.second.x, pos.second.y) == connection) {
//                        auto& door = ecs.get_component<Door>(pos.first);
//                        auto& door_render = ecs.get_component<Renderable>(pos.first);
//                        if (door.d_status) {
//                            door.d_status = false;
//                            door_render.glyph = DOOR;
//                            level.m_blocked_tiles[connection] = false;
//                            
//                        } else {
//                            door.d_status = true;
//                            door_render.glyph = LEFT_OPEN_DOOR;
//                            level.m_blocked_tiles[connection] = true;
//                        }
//                    }
//                }
//            }
//            ecs.remove_component<WantsToToggleConnections>(entity);
//        }
//    }
//};
