#ifndef GAME_LOG_H_
#define GAME_LOG_H_

#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>

class GameLog {
    std::vector<std::string> log_list;
    const int MAX_WIDTH = 78;
    const int MAX_LOG_LINES = 13;
    int current_line = 1;

public:
    WINDOW* gamelog;

    void init() {
        gamelog = newwin(15, 80, 16, 0);
        box(gamelog, ACS_VLINE, ACS_HLINE);
        wmove(gamelog, 0, 4);
        wprintw(gamelog, "Journal");
        printlog("Welcome to ECAN!");
    }

    void printlog(const char* phrase) {
        log_list.push_back(phrase);

        if (current_line <= MAX_LOG_LINES) {
            wmove(gamelog, current_line, 1);
            wprintw(gamelog, "%s", log_list.back().c_str());
            ++current_line;
        } else {
            // First clear all the window.
            wmove(gamelog, 1, 1);
            //std::cout << "clearing gamelog" << std::endl;
            for (int i = 1; i <= MAX_LOG_LINES; i++) {
                for (int j = 1; j <= MAX_WIDTH; j++) {
                    wmove(gamelog, i, j);
                    wprintw(gamelog, " ");
                }
            }
            //std::cout << "erasing the last message" << std::endl;
            log_list.erase(log_list.begin());
            for (current_line = 13; current_line >= 1; current_line--) {
                //std::cout << "printing current message" << std::endl;
                wmove(gamelog, current_line, 1);
                wprintw(gamelog, "%s", log_list.at(current_line - 1).c_str());
            }
            // Set the current_line to ensure that it doesn't overwrite
            // any lines.
            current_line = 14;
        }
    }
};

#endif
