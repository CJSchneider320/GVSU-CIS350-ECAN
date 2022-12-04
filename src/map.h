#include <string>
#include <vector>
#include <ncurses.h>

#include "colordata.h"

enum TileType {
    Floor,
    Wall,
};

class Map {

public:
    std::vector<TileType> m_tiles;
    std::vector<bool> m_blocked_tiles;
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
                    glyph = " ";
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
            if (tile == '#') {
                m_tiles.push_back(TileType::Wall);
                m_blocked_tiles.push_back(true);
            } else if (tile == '.') {
                m_tiles.push_back(TileType::Floor);
                m_blocked_tiles.push_back(false);
            }
        }
    }
};
