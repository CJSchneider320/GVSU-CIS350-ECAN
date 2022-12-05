#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>
#include <ncurses.h>

#include "colordata.h"
#include "components.h"
#include "chars.h"
#include "world.h"

enum TileType {
    Floor,
    Wall,
    Spike,
    DoorTile,
    LeverTile,
    Unknown,
};

enum DoorStatus {
    Open,
    Closed,
};

class Map {

public:
    std::vector<TileType> m_tiles;
    std::vector<bool> m_blocked_tiles;
    std::vector<Entity> m_doors;
    std::vector<std::vector<Entity>> m_tile_contents;
    int m_player_start = 0;
    int m_height = 15;
    int m_width = 20;

    void draw_level(WINDOW* room, World& ecs) {
        int x = 0;
        int y = 0;
        std::string glyph;
        int color;
        int index = 0;

        for (TileType tile : m_tiles) {
            wmove(room, y, x);
            switch (tile) {
                case TileType::Floor:
                    glyph = ".";
                    color = FWHITEBBLACK;
                    break;
                case TileType::Wall:
                    glyph = "#";
                    color = FWHITEBBLACK;
                    break;
                case TileType::Spike:
                    glyph = SPIKE;
                    color = FWHITEBBLACK;
                    break;
                case TileType::DoorTile:
                case TileType::LeverTile:
                    break;
                default:
                    glyph = "?";
                    color = FWHITEBBLACK;
                   break;
            }
            wattron(room, COLOR_PAIR(color));
            wprintw(room, "%s", glyph.c_str());
            wattroff(room, COLOR_PAIR(color));

            x += 1;
            if (x == m_width) {
                x = 0;
                y += 1;
            }
        }
    }

    void create_preset_level(std::string a_level, std::unordered_map<int, std::vector<int>> connections, World& ecs) {
        int index = 0;
        for (char tile : a_level) {
            switch (tile) {
                case '#':
                    m_tiles.push_back(TileType::Wall);
                    m_blocked_tiles.push_back(true);
                    m_tile_contents.push_back(std::vector<Entity>());
                    break;
                case '.':
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(false);
                    m_tile_contents.push_back(std::vector<Entity>());
                    break;
                case '@':
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(false);
                    m_player_start = a_level.find('@');
                    m_tile_contents.push_back(std::vector<Entity>());
                    break;
                case '!':
                    m_tiles.push_back(TileType::Spike);
                    m_blocked_tiles.push_back(false);
                    m_tile_contents.push_back(std::vector<Entity>());
                    break;
                case 'D':
                {
                    m_tiles.push_back(TileType::DoorTile);
                    m_blocked_tiles.push_back(true);
                    Entity door = ecs.create_entity();
                    ecs.add_component(door, Door {false});
                    ecs.add_component(door, index_to_position(index));
                    ecs.add_component(door, Renderable {std::string(DOOR), FYELLOWBBLACK});
                    m_doors.push_back(door);
                    m_tile_contents.push_back(std::vector<Entity>({door}));
                    break;
                }
                case 'd':
                {
                    m_tiles.push_back(TileType::DoorTile);
                    m_blocked_tiles.push_back(false);
                    Entity door = ecs.create_entity();
                    ecs.add_component(door, Door {true});
                    ecs.add_component(door, index_to_position(index));
                    ecs.add_component(door, Renderable {std::string(LEFT_OPEN_DOOR), FYELLOWBBLACK});
                    m_doors.push_back(door);
                    m_tile_contents.push_back(std::vector<Entity>(door));
                    break;
                }
                case 'l':
                {
                    m_tiles.push_back(TileType::LeverTile);
                    m_blocked_tiles.push_back(false);
                    Entity lever = ecs.create_entity();
                    ecs.add_component(lever,
                        Renderable { LEVER_OFF, FGREENBBLACK });
                    ecs.add_component(lever,
                        index_to_position(index));
                    ecs.add_component(lever, Connection { connections[index] });
                    ecs.add_component(lever, Lever { false });
                    ecs.add_component(lever, Interactable {});
                    m_tile_contents.push_back(std::vector<Entity>(lever));
                    break;
                }
                case 'L':
                {
                    m_tiles.push_back(TileType::LeverTile);
                    m_blocked_tiles.push_back(false);
                    Entity lever = ecs.create_entity();
                    ecs.add_component(lever,
                        Renderable { LEVER_ON, FGREENBBLACK });
                    ecs.add_component(lever,
                        index_to_position(index));
                    ecs.add_component(lever, Connection { connections[index] });
                    ecs.add_component(lever, Lever { true });
                    ecs.add_component(lever, Interactable {});
                    m_tile_contents.push_back(std::vector<Entity>(lever));
                    break;
                }
                default:
                    m_tiles.push_back(TileType::Unknown);
                    m_blocked_tiles.push_back(true);
                    m_tile_contents.push_back(std::vector<Entity>());
                    break;
            }
            ++index;
        }
    }

    Position index_to_position(int index) {
        Position pos;
        pos.x = index % m_width;
        pos.y = index / m_width;

        return pos;
    }

    int position_to_index(int x, int y) {
        return (y * (m_width)) + x;
    }
};

#endif
