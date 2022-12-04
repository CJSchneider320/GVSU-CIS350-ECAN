#include <string>
#include <vector>
#include <ncurses.h>

#include "colordata.h"
#include "components.h"

enum TileType {
    Floor,
    Wall,
    Unknown,
};

class Map {

public:
    std::vector<TileType> m_tiles;
    std::vector<bool> m_blocked_tiles;
    int m_player_start = 0;
    int m_height = 15;
    int m_width = 20;

    void draw_level(WINDOW* room) {
        int x = 0;
        int y = 0;
        std::string glyph;
        int color;
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

    void create_preset_level(std::string a_level) {
        for (char tile : a_level) {
            switch (tile) {
                case '#':
                    m_tiles.push_back(TileType::Wall);
                    m_blocked_tiles.push_back(true);
                    break;
                case '.':
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(false);
                    break;
                case '@':
                    m_tiles.push_back(TileType::Floor);
                    m_blocked_tiles.push_back(false);
                    m_player_start = a_level.find('@');
                    break;
                default:
                    m_tiles.push_back(TileType::Unknown);
                    m_blocked_tiles.push_back(true);
                    break;
            }
        }
    }

    Position index_to_positon(int index) {
        Position pos {
            m_player_start % m_width,
            m_player_start / m_width
        };

        return pos;
    }
};
