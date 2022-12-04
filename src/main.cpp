#include <ncurses.h>
#include <locale>
#include <string>

#include "map.h"
#include "world.h"


int main() {
    // ---------------------------------------------------------------
    // preliminary set up for ncurses to use support all characters
    // and start colors.
    setlocale(LC_ALL, "");
    initscr();

    if (!has_colors()) {
        printw("This terminal does not support color.");
        mvprintw(1, 0, "Please use a terminal that does support color.");
        getch();
        return -1;
    }
    
    noecho();
    start_color();
    // ---------------------------------------------------------------

    // ---------------------------------------------------------------
    // Initialize colors.
    init_pair(FWHITEBBLACK, COLOR_WHITE, COLOR_BLACK);

    // ---------------------------------------------------------------
    // Define levels
    std::string baseline_level;
    baseline_level += "####################";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "####################";

    std::string level_1;
    level_1 += "####################"; // 1
    level_1 += "#...#.....#........#"; // 2
    level_1 += "#.c.D..l..#.S......#"; // 3
    level_1 += "#...#.....#........#"; // 4
    level_1 += "#####.....#######d##"; // 5
    level_1 += "#...#.....#........#"; // 6
    level_1 += "#...D..l..D........#"; // 7
    level_1 += "#...#.....#........#"; // 8
    level_1 += "#...#.....#!!!!!!!!#"; // 9
    level_1 += "#...#.....#........#"; // 10
    level_1 += "#...#.....#........#"; // 11
    level_1 += "#.@.#.....#........#"; // 12
    level_1 += "#...#.....#........#"; // 13
    level_1 += "####################"; // 14
    // ---------------------------------------------------------------

    Map level;
    // ---------------------------------------------------------------
    // Initialize the ECS.
    World ecs;
    ecs.init();
    ecs.register_component<Position>();
    ecs.register_component<Renderable>();
    // ---------------------------------------------------------------

    level.create_preset_level(level_1);

    // Create Player entity
    Entity player = ecs.create_entity();
    ecs.add_component(player, level.index_to_positon(level.m_player_start));
    ecs.add_component(player, Renderable { "@", FWHITEBBLACK });

    WINDOW* room = newwin(level.m_height, level.m_width, 5, 10);

    int player_input;
    bool quit = false;

    while (!quit) {
        level.draw_level(room);

        std::string player_glyph = ecs.get_component<Renderable>(player).glyph;
        int player_color = ecs.get_component<Renderable>(player).symbol_color;
        int player_x = ecs.get_component<Position>(player).x;
        int player_y = ecs.get_component<Position>(player).y;

        wmove(room, player_y, player_x);
        wattron(room, COLOR_PAIR(player_color));
        wprintw(room, "%s", player_glyph.c_str());
        wattroff(room, COLOR_PAIR(player_color));

        refresh();
        wrefresh(room);

        player_input = getch();
        if (player_input == 'q') {
            quit = true;
        } else {
            continue;
        }
    }

    endwin();
    
    return 0;
}
