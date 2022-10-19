/*
 * Author: Nathaniel Tabacchi
 * Based on artistic depiction by Alex Hobbs.
 *
 * ver. 20221019
 *
 * Note:
 *	I know there's better ways to do almost all of what's in this file,
 *	this is simply a hacked-together mockup to make an image.
 *	- Nathaniel C. Tabacchi
 */
#include <ncurses.h>
#include <locale.h>
#include "chars.h"

int main (int argc, char** argv)
{
	setlocale(LC_ALL, "");
	initscr();
	
	if (!has_colors()) {
		printw("This terminal does not support color.");
		mvprintw(1, 0, "It is recommended to use the Windows Terminal with WSL.");
		getch();
		return -1;
	}

	// Start colors & initialize color pairs
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);

	int height, width, start_y, start_x;
	width = 20;
	height = 15;
	start_y = start_x = 10;
	WINDOW* room = newwin(height, width, start_y, start_x);
	refresh();

	// Create Walls
	// Corner Walls
	wmove(room, 0, 0);
	wprintw(room, "%s", TOP_LEFT_WALL);
	wmove(room, 8, 4);
	wprintw(room, "%s", TOP_LEFT_WALL);
	wmove(room, 8, 15);
	wprintw(room, "%s", TOP_LEFT_WALL);
	wmove(room, 0, 19);
	wprintw(room, "%s", TOP_RIGHT_WALL);
	wmove(room, 11, 11);
	wprintw(room, "%s", TOP_RIGHT_WALL);
	wmove(room, 14, 0);
	wprintw(room, "%s", BOTTOM_LEFT_WALL);
	wmove(room, 4, 7);
	wprintw(room, "%s", BOTTOM_LEFT_WALL);
	wmove(room, 14, 19);
	wprintw(room, "%s", BOTTOM_RIGHT_WALL);
	wmove(room, 4, 13);
	wprintw(room, "%s", BOTTOM_RIGHT_WALL);

	// Top Walls
	wmove(room, 0, 1);
	for (int i = 1; i < 19; i++) {
		wprintw(room, "%s", HORIZONTAL_WALL);
	}

	// Bottom Walls
	wmove(room, 14, 1);
	for (int i = 1; i < 19; i++) {
		wprintw(room, "%s", HORIZONTAL_WALL);	
	}
	
	// Left Walls
	for (int i = 1; i < 14; i++) {
		wmove(room, i, 0);
		wprintw(room, "%s", VERTICAL_WALL);	
	}

	// Right Walls
	for (int i = 1; i < 14; i++) {
		wmove(room, i, 19);
		wprintw(room, "%s", VERTICAL_WALL);	
	}

	// Intersecting Walls
	wmove(room, 0, 7);
	wprintw(room, "%s", TOP_MIDDLE_WALL);
	wmove(room, 0, 13);
	wprintw(room, "%s", TOP_MIDDLE_WALL);
	wmove(room, 11, 8);
	wprintw(room, "%s", TOP_MIDDLE_WALL);
	wmove(room, 2, 7);
	wprintw(room, "%s", LEFT_MIDDLE_WALL);
	wmove(room, 11, 4);
	wprintw(room, "%s", LEFT_MIDDLE_WALL);
	wmove(room, 10, 15);
	wprintw(room, "%s", LEFT_MIDDLE_WALL);
	wmove(room, 14, 4);
	wprintw(room, "%s", BOTTOM_MIDDLE_WALL);
	wmove(room, 14, 8);
	wprintw(room, "%s", BOTTOM_MIDDLE_WALL);
	wmove(room, 14, 11);
	wprintw(room, "%s", BOTTOM_MIDDLE_WALL);
	wmove(room, 14, 15);
	wprintw(room, "%s", BOTTOM_MIDDLE_WALL);
	wmove(room, 2, 19);
	wprintw(room, "%s", RIGHT_MIDDLE_WALL);
	wmove(room, 8, 19);
	wprintw(room, "%s", RIGHT_MIDDLE_WALL);
	wmove(room, 10, 19);
	wprintw(room, "%s", RIGHT_MIDDLE_WALL);
	wmove(room, 2, 13);
	wprintw(room, "%s", CROSS_WALL);

	// Vertical Walls
	wmove(room, 1, 7);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 3, 7);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 1, 13);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 3, 13);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 9, 4);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 10, 4);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 12, 4);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 13, 4);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 12, 8);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 13, 8);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 12, 11);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 13, 11);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 11, 15);
	wprintw(room, "%s", VERTICAL_WALL);
	wmove(room, 13, 15);
	wprintw(room, "%s", VERTICAL_WALL);
	
	// Horizontal Walls
	wmove(room, 2, 8);
	for (int i = 1; i < 6; i++) {
		wprintw(room, "%s", HORIZONTAL_WALL);
		wmove(room, 2, 8 + i);
	}

	wmove(room, 2, 14);
	for (int i = 1; i < 6; i++) {
		wprintw(room, "%s", HORIZONTAL_WALL);
		wmove(room, 2, 14 + i);
	}

	wmove(room, 4, 8);
	for (int i = 1; i < 6; i++) {
		wprintw(room, "%s", HORIZONTAL_WALL);
		wmove(room, 4, 8 + i);
	}

	wmove(room, 8, 5);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 8, 7);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 8, 8);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 8, 16);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 8, 18);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 11, 5);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 11, 7);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 11, 9);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 11, 10);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 10, 16);
	wprintw(room, "%s", HORIZONTAL_WALL);
	wmove(room, 10, 18);
	wprintw(room, "%s", HORIZONTAL_WALL);

	// Doors
	wattron(room, COLOR_PAIR(1));
	wmove(room, 8, 6);
	wprintw(room, "%s", LOCKED_DOOR);
	wmove(room, 11, 6);
	wprintw(room, "%s", LEFT_OPEN_DOOR);
	wattroff(room, COLOR_PAIR(1));

	wattron(room, COLOR_PAIR(2));
	wmove(room, 9, 15);
	wprintw(room, "%s", LOCKED_DOOR);
	wmove(room, 10, 17);
	wprintw(room, "%s", LEFT_OPEN_DOOR);
	wattroff(room, COLOR_PAIR(2));

	wattron(room, COLOR_PAIR(3));
	wmove(room, 8, 17);
	wprintw(room, "%s", LOCKED_DOOR);
	wmove(room, 12, 15);
	wprintw(room, "%s", TOP_OPEN_DOOR);
	wattroff(room, COLOR_PAIR(3));

	// Spikes
	wmove(room, 8, 9);
	for (int i = 1; i < 7; i++) {
		wprintw(room, "%s", SPIKE);
		wmove(room, 8, 9 + i);
	}

	// Stairs
	wmove(room, 13, 2);
	wprintw(room, "%s", STAIRS_ENTER);
	wmove(room, 13, 17);
	wprintw(room, "%s", STAIRS_EXIT);

	// Levers
	wattron(room, COLOR_PAIR(4));
	wmove(room, 1, 6);
	wprintw(room, "%c", '/');
	wattroff(room, COLOR_PAIR(4));

	wattron(room, COLOR_PAIR(1));
	wmove(room, 7, 4);
	wprintw(room, "%c", '\\');
	wattroff(room, COLOR_PAIR(4));

	wmove(room, 1, 17);
	wprintw(room, "%c", '\\');
	wmove(room, 1, 18);
	wprintw(room, "%c", '/');

	// Plates
	wattron(room, COLOR_PAIR(2));
	wmove(room, 1, 8);
	wprintw(room, "%s", HEAVY_PRESSURE_PLATE);
	wattroff(room, COLOR_PAIR(2));

	wmove(room, 1, 12);
	wprintw(room, "%s", HEAVY_PRESSURE_PLATE);

	wmove(room, 1, 14);
	wprintw(room, "%s", HEAVY_PRESSURE_PLATE);
	
	wmove(room, 3, 8);
	wprintw(room, "%s", HEAVY_PRESSURE_PLATE);

	wattron(room, COLOR_PAIR(3));
	wmove(room, 3, 12);
	wprintw(room, "%s", HEAVY_PRESSURE_PLATE);
	wattroff(room, COLOR_PAIR(3));

	wmove(room, 1, 16);
	wprintw(room, "%s", PRESSURE_PLATE);

	// Buttons
	wmove(room, 1, 15);
	wprintw(room, "%s", BUTTON);

	// Chests
	wmove(room, 13, 6);
	wprintw(room, "%s", CHEST);

	// Arrows
	wattron(room, COLOR_PAIR(5));
	wmove(room, 1, 4);
	wprintw(room, "%s", LEFT_ARROW);
	wattroff(room, COLOR_PAIR(5));

	wattron(room, COLOR_PAIR(2));
	wmove(room, 1, 9);
	wprintw(room, "%s", RIGHT_ARROW);
	wmove(room, 1, 11);
	wprintw(room, "%s", LEFT_ARROW);
	wmove(room, 3, 9);
	wprintw(room, "%s", LEFT_ARROW);
	wmove(room, 3, 11);
	wprintw(room, "%s", RIGHT_ARROW);
	wattroff(room, COLOR_PAIR(2));

	// Robots
	/* A note I want to make here:
	 * A blue robot is a regular robot.
	 * A red robot is an anti-robot.
	 */
	wattron(room, COLOR_PAIR(1));
	wmove(room, 1, 10);
	wprintw(room, "%s", ROBOT);
	wattroff(room, COLOR_PAIR(1));

	wattron(room, COLOR_PAIR(2));
	wmove(room, 3, 10);
	wprintw(room, "%s", ROBOT);
	wattroff(room, COLOR_PAIR(2));

	// Player
	wmove(room, 5, 4);
	wprintw(room, "%s", PLAYER);

	// Finally, move the cursor off-screen for screenshot
	curs_set(0);

	wrefresh(room);
	getch();

	endwin();
	return 0;
}
