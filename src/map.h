#include <string>
#include <vector>
#include <ncurses.h>

enum TileType {
    Floor,
    Wall,
};

class Map {

public:
    std::vector<TileType> m_tiles;
    int m_height = 15;
    int m_width = 20;

    void draw_level(WINDOW* room) {
        int x = 0;
        int y = 0;
        std::string glyph;
        for (TileType tile : m_tiles) {
            wmove(room, y, x);
            switch (tile) {
                case TileType::Floor:
                   wprintw(room, "."); 
                   break;
                case TileType::Wall:
                   wprintw(room, "#");
                   break;
                default:
                   wprintw(room, " ");
                   break;
            }
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
            } else if (tile == '.') {
                m_tiles.push_back(TileType::Floor);
            }
        }
    }
};
