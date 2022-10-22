#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "level_renderer.h"
#include "chars.h"

using namespace std;

/* Assumes ncurses has already been started.
 * renderLevel will create a window sized appropriately for the level,
 * and draw that level to the window. It assumes that the terminal is 
 * 80 characters by 30 lines.
 * returns: an ncurses window object.
 */
 WINDOW* LevelRenderer::renderLevel(Level level)
 {
 	int start_y = 15 - (level.getHeight() / 2);
	int start_x = 40 - (level.getWidth() / 2);
	int map_index;
	char floor_tiles[4] = {'.', ',', '`', '\''};
	char floor_tile; // tile to be used for current floor
	WINDOW* room = newwin(level.getHeight(), level.getWidth(),
		start_y, start_x);

	srand(time(NULL));
	for (int y = 0; y < level.getHeight(); y++) {
		for (int x = 0; x < level.getWidth(); x++) {
			wmove(room, y, x);
			map_index = y * level.getWidth() + x;

			// ---------------- BEGIN WALLS ----------------
			if (level.getMap()[map_index] == '#') {
				// These store the tile in the named direction of this tile
				char top, right, bottom, left;
				// These store whether that tile is a wall
				bool top_wall, right_wall, bottom_wall, left_wall;
				// Get the tiles in each direction
				if (y != 0)
					top = level.getMap()[(y - 1) * level.getWidth() + x];
				else top = 0;
				if (x != 0)
					left = level.getMap()[y * level.getWidth() + (x - 1)];
				else left = 0;
				if (y != level.getHeight() - 1)
					bottom = level.getMap()[(y + 1) * level.getWidth() + x];
				else bottom = 0;
				if (x != level.getWidth() - 1)
					right = level.getMap()[y * level.getWidth() + (x + 1)];
				else right = 0;
				// Check if the tiles are walls
				top_wall = (top == '#');
				right_wall = (right == '#');
				bottom_wall = (bottom == '#');
				left_wall = (left == '#');
				// Determine what wall to render
				// Straight walls
				if ((left_wall && right_wall && !top_wall && !bottom_wall)
					|| (!left_wall && right_wall && !top_wall && !bottom_wall)
					|| (left_wall && !right_wall && !top_wall && !bottom_wall))
					wprintw(room, HORIZONTAL_WALL);
				else if ((!left_wall && !right_wall && top_wall && bottom_wall)
					|| (!left_wall && !right_wall && top_wall && !bottom_wall)
					|| (!left_wall && !right_wall && !top_wall && bottom_wall))
					wprintw(room, VERTICAL_WALL);
				// Corner walls
				else if (!left_wall && right_wall && !top_wall && bottom_wall)
					wprintw(room, TOP_LEFT_WALL);
				else if (left_wall && !right_wall && !top_wall && bottom_wall)
					wprintw(room, TOP_RIGHT_WALL);
				else if (!left_wall && right_wall && top_wall && !bottom_wall)
					wprintw(room, BOTTOM_LEFT_WALL);
				else if (left_wall && !right_wall && top_wall && !bottom_wall)
					wprintw(room, BOTTOM_RIGHT_WALL);
				// Intersecting walls
				else if (!left_wall && right_wall && top_wall && bottom_wall)
					wprintw(room, LEFT_MIDDLE_WALL);
				else if (left_wall && !right_wall && top_wall && bottom_wall)
					wprintw(room, RIGHT_MIDDLE_WALL);
				else if (left_wall && right_wall && !top_wall && bottom_wall)
					wprintw(room, TOP_MIDDLE_WALL);
				else if (left_wall && right_wall && top_wall && !bottom_wall)
					wprintw(room, BOTTOM_MIDDLE_WALL);
				else if (left_wall && right_wall && top_wall && bottom_wall)
					wprintw(room, CROSS_WALL);
			}
			// ---------------- END WALLS ----------------
			// Floors
			else if (level.getMap()[map_index] == '.') {
				floor_tile = floor_tiles[rand() % 4];
				wprintw(room, "%c", floor_tile);
			}
		}
	}

	return room;
}
