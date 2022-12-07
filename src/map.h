#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>
#include <ncurses.h>

#include "colordata.h"
#include "components.h"
#include "chars.h"
#include "world.h"
#include "game_log.h"

extern GameLog gamelog;

enum TileType {
    Floor = 0,
    Wall = 1,
    SpikeTile = 2,
    DoorTile = 3,
    LeverTile = 4,
    StairsEnter = 5,
    StairsExit = 6,
    ChestTile = 7,
    PressurePlateTile = 8,
    Unknown = 9,
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
    std::vector<std::set<Entity>> m_tile_contents;
    std::vector<std::string> m_tile_glyphs;
    std::vector<char> floor_tiles = {'.', ',', '`', '\"', '\''};
    int m_current_level = -1;
    int m_previous_level = -1;
    int m_player_start = 0;
    int m_height = 15;
    int m_width = 20;

    void draw_level(WINDOW* room, World& ecs) {
        int x = 0;
        int y = 0;
        std::string glyph;
        int color;
        int emphasis;
        int index = 0;

        for (TileType tile : m_tiles) {
            emphasis = 0;
            wmove(room, y, x);
            switch (tile) {
                case TileType::Floor:
                {
                    glyph = m_tile_glyphs[index];
                    color = FWHITEBBLACK;
                    break;
                }
                case TileType::Wall:
                {
                    glyph = m_tile_glyphs[index];
                    color = FWHITEBBLACK;
                    emphasis = A_BOLD;
                    break;
                }
                case TileType::SpikeTile:
                case TileType::DoorTile:
                case TileType::LeverTile:
                case TileType::StairsEnter:
                case TileType::StairsExit:
                case TileType::ChestTile:
                case TileType::PressurePlateTile:
                    break;
                case Unknown:
                default:
                    glyph = "?";
                    color = FMAGENTABBLACK;
                   break;
            }
            wattron(room, COLOR_PAIR(color) | emphasis);
            wprintw(room, "%s", glyph.c_str());
            wattroff(room, COLOR_PAIR(color) | emphasis);

            x += 1;
            if (x == m_width) {
                x = 0;
                y += 1;
            }

            ++index;
        }
    }

    void create_preset_level(std::string a_level, std::unordered_map<int, std::vector<int>> connections, Entity player, World& ecs) {
        std::srand((unsigned) time(NULL));
        int index = 0;
        for (char tile : a_level) {
            switch (tile) {
                case '#':
                {
                    m_tiles.push_back(TileType::Wall);
                    m_blocked_tiles.push_back(true);
                    m_tile_contents.push_back(std::set<Entity>{});
                    m_tile_glyphs.push_back(wall_glyph(a_level, index));
                    break;
                }
                case '.':
                {
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(false);
                    m_tile_contents.push_back(std::set<Entity>{});
                    std::string glyph = "";
                    glyph += floor_tiles[rand() % 5];
                    m_tile_glyphs.push_back(glyph);
                    break;
                }
                case '@':
                {
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(false);
                    m_player_start = a_level.find('@');
                    m_tile_contents.push_back(std::set<Entity>{player});
                    std::string glyph;
                    glyph = floor_tiles[rand() % 5];
                    m_tile_glyphs.push_back(glyph);
                    break;
                }
                case '!':
                {
                    m_tiles.push_back(TileType::SpikeTile);
                    m_blocked_tiles.push_back(false);
                    Entity spike = ecs.create_entity();
                    ecs.add_component(spike, Spike { false });
                    ecs.add_component(spike, index_to_position(index));
                    ecs.add_component(spike,
                            Renderable { SPIKE, FREDBBLACK });
                    m_tile_contents.push_back(std::set<Entity>{spike});
                    m_tile_glyphs.push_back(SPIKE);
                    break;
                }
                case 'D':
                {
                    m_tiles.push_back(TileType::DoorTile);
                    m_blocked_tiles.push_back(true);
                    Entity door = ecs.create_entity();
                    ecs.add_component(door, Door {false});
                    ecs.add_component(door, index_to_position(index));
                    ecs.add_component(door, Renderable {std::string(DOOR), FYELLOWBBLACK, 0});
                    m_doors.push_back(door);
                    m_tile_contents.push_back(std::set<Entity>{door});
                    m_tile_glyphs.push_back(DOOR);
                    break;
                }
                case 'd':
                {
                    m_tiles.push_back(TileType::DoorTile);
                    m_blocked_tiles.push_back(false);
                    Entity door = ecs.create_entity();
                    ecs.add_component(door, Door {true});
                    ecs.add_component(door, index_to_position(index));
                    ecs.add_component(door, Renderable {std::string(LEFT_OPEN_DOOR), FYELLOWBBLACK, 0});
                    m_doors.push_back(door);
                    m_tile_contents.push_back(std::set<Entity>{door});
                    m_tile_glyphs.push_back(LEFT_OPEN_DOOR);
                    break;
                }
                case 'l':
                {
                    m_tiles.push_back(TileType::LeverTile);
                    m_blocked_tiles.push_back(false);
                    Entity lever = ecs.create_entity();
                    ecs.add_component(lever,
                        Renderable { LEVER_OFF, FGREENBBLACK, 0});
                    ecs.add_component(lever,
                        index_to_position(index));
                    ecs.add_component(lever, Connection { connections[index] });
                    ecs.add_component(lever, Lever { false });
                    ecs.add_component(lever, Interactable {});
                    m_tile_contents.push_back(std::set<Entity>{lever});
                    m_tile_glyphs.push_back(LEVER_OFF);
                    break;
                }
                case 'L':
                {
                    m_tiles.push_back(TileType::LeverTile);
                    m_blocked_tiles.push_back(false);
                    Entity lever = ecs.create_entity();
                    ecs.add_component(lever,
                        Renderable { LEVER_ON, FGREENBBLACK, 0 });
                    ecs.add_component(lever, index_to_position(index));
                    ecs.add_component(lever, Connection { connections[index] });
                    ecs.add_component(lever, Lever { true });
                    ecs.add_component(lever, Interactable {});
                    m_tile_contents.push_back(std::set<Entity>{lever});
                    m_tile_glyphs.push_back(LEVER_ON);
                    break;
                }
                case 'S':
                {
                    m_tiles.push_back(TileType::StairsExit);
                    m_blocked_tiles.push_back(false);
                    Entity stairs_exit = ecs.create_entity();
                    ecs.add_component(stairs_exit, Stairs { true });
                    ecs.add_component(stairs_exit,
                            Renderable {STAIRS_EXIT, FCYANBBLACK, 0});
                    ecs.add_component(stairs_exit, index_to_position(index));
                    m_tile_contents.push_back(std::set<Entity>{stairs_exit});
                    m_tile_glyphs.push_back(STAIRS_EXIT);
                    break;
                }
                case 's':
                {
                    m_tiles.push_back(TileType::StairsEnter);
                    m_blocked_tiles.push_back(false);
                    Entity stairs_enter = ecs.create_entity();
                    ecs.add_component(stairs_enter, Stairs { false });
                    ecs.add_component(stairs_enter,
                            Renderable {STAIRS_ENTER, FCYANBBLACK, 0});
                    ecs.add_component(stairs_enter, index_to_position(index));
                    m_tile_contents.push_back(std::set<Entity>{stairs_enter});
                    m_tile_glyphs.push_back(STAIRS_ENTER);
                    break;
                }
                case 'c':
                {
                    int gold = 1 + std::rand() % 100;
                    m_tiles.push_back(TileType::ChestTile);
                    m_blocked_tiles.push_back(false);
                    Entity chest = ecs.create_entity();
                    ecs.add_component(chest, index_to_position(index));
                    ecs.add_component(chest,
                            Renderable {CHEST, FYELLOWBBLACK, 1});
                    ecs.add_component(chest, Chest {false, gold} );
                    m_tile_contents.push_back(std::set<Entity>{chest});
                    m_tile_glyphs.push_back(CHEST);
                    break;
                }
                case 'p':
                {
                    m_tiles.push_back(TileType::PressurePlateTile);
                    m_blocked_tiles.push_back(false);
                    Entity plate = ecs.create_entity();
                    ecs.add_component(plate, index_to_position(index));
                    ecs.add_component(plate,
                            Renderable { PRESSURE_PLATE, FMAGENTABBLACK, 0 });
                    ecs.add_component(plate, Connection { connections[index] });
                    ecs.add_component(plate, PressurePlate { false });
                    m_tile_contents.push_back(std::set<Entity>{plate});
                    m_tile_glyphs.push_back(PRESSURE_PLATE);
                    break;
                }
                case 'R':
                {
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(true);
                    Entity robot = ecs.create_entity();
                    ecs.add_component(robot, Robot {});
                    ecs.add_component(robot, index_to_position(index));
                    ecs.add_component(robot,
                            Renderable { ROBOT, FBLUEBBLACK, 2 });
                    ecs.add_component(robot, Ambulates {});
                    m_tile_contents.push_back(std::set<Entity>{robot});
                    std::string glyph;
                    glyph = floor_tiles[rand() % 5];
                    m_tile_glyphs.push_back(glyph);
                    break;
                }
                default:
                    m_tiles.push_back(TileType::Unknown);
                    m_blocked_tiles.push_back(true);
                    m_tile_contents.push_back(std::set<Entity>{});
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

    std::string wall_glyph(std::string level, int index) {
        uint8_t mask = 0;
        Position this_pos = index_to_position(index);
        // check the cardinal directions for walls or doors.
        if (this_pos.x != 0) {
            if (level[position_to_index(this_pos.x - 1, this_pos.y)] == '#'
                || level[position_to_index(this_pos.x - 1, this_pos.y)] == 'D'
                || level[position_to_index(this_pos.x - 1, this_pos.y)] == 'd') {
                mask += 1;
            }
        }
        if (this_pos.x != 19) {
            if (level[position_to_index(this_pos.x + 1, this_pos.y)] == '#'
                || level[position_to_index(this_pos.x + 1, this_pos.y)] == 'D'
                || level[position_to_index(this_pos.x + 1, this_pos.y)] == 'd') {
                mask += 2;
            }
        }
        if (this_pos.y != 0) {
            if (level[position_to_index(this_pos.x, this_pos.y - 1)] == '#'
                || level[position_to_index(this_pos.x, this_pos.y - 1)] == 'D'
                || level[position_to_index(this_pos.x, this_pos.y - 1)] == 'd') {
                mask += 4;
            }
        }
        if (this_pos.y != 14) {
            if (level[position_to_index(this_pos.x, this_pos.y + 1)] == '#'
                || level[position_to_index(this_pos.x, this_pos.y + 1)] == 'D'
                || level[position_to_index(this_pos.x, this_pos.y + 1)] == 'd') {
                mask += 8;
            }
        }
        
        switch (mask) {
            case 1:
                return RIGHT_END_WALL;
            case 2:
                return LEFT_END_WALL;
            case 3:
                return HORIZONTAL_WALL;
            case 4:
                return BOTTOM_END_WALL;
            case 5:
                return BOTTOM_RIGHT_WALL;
            case 6:
                return BOTTOM_LEFT_WALL;
            case 7:
                return BOTTOM_MIDDLE_WALL;
            case 8:
                return TOP_END_WALL;
            case 9:
                return TOP_RIGHT_WALL;
            case 10:
                return TOP_LEFT_WALL;
            case 11:
                return TOP_MIDDLE_WALL;
            case 12:
                return VERTICAL_WALL;
            case 13:
                return RIGHT_MIDDLE_WALL;
            case 14:
                return LEFT_MIDDLE_WALL;
            case 15:
                return CROSS_WALL;
            default:
                return "#";
        }
    }

};

#endif
