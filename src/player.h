#include <ncurses.h>

class Player {
    static void try_move_player() {
        
    }

    static void player_input() {
        int player_input = getch();
        if (player_input == 'q') {
            quit = true;
        } else {
            continue;
        }
    }
};
