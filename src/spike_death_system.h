#ifndef SPIKE_DEATH_SYSTEM_H_
#define SPIKE_DEATH_SYSTEM_H_

#include "system.h"
#include "world.h"
#include "components.h"

class SpikeDeathSystem : public System {
public:
    void run(World& ecs) override {
        for (Entity entity : entities) {
            auto& spike = ecs.get_component<Spike>(entity);
            if (spike.is_stood_on) {
                auto& players = ecs.get_component_map<CPlayer>()->component_map;
                for (auto& player : players) {
                    ecs.add_component(player.first, Dead {});
                }
            }
        }
    }
};

#endif
