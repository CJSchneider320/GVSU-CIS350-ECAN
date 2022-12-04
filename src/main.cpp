#include <ncurses.h>
#include <locale>
#include <string>

#include "map.h"
#include "world.h"


int main() {
    setlocale(LC_ALL, "");
    initscr();

    if (!has_colors()) {
        printw("This terminal does not support color.");
        mvprintw(1, 0, "Please use a terminal that does support color.");
        getch();
        return -1;
    }

    start_color();


    init_pair(FWHITEBBLACK, COLOR_WHITE, COLOR_BLACK);

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
    baseline_level += "####################";

    Map level;
    World ecs;

    level.create_preset_level(baseline_level);

    WINDOW* room = newwin(level.m_height, level.m_width, 5, 10);

    level.draw_level(room);

    refresh();
    wrefresh(room);
    getch();
    endwin();
    
    return 0;
}
