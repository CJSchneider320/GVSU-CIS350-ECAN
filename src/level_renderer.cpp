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
	WINDOW* room = newwin(level.getHeight(), level.getWidth(),
		start_y, start_x);
	struct WDBRT wd;

	srand(time(NULL));
	for (int y = 0; y < level.getHeight(); y++) {
		for (int x = 0; x < level.getWidth(); x++) {
			wmove(room, y, x);
			map_index = y * level.getWidth() + x;
			// ---------------- BEGIN WALLS ----------------
			if (level.getMap()[map_index] == '#') {
				// Check if adjacent tiles are walls or doors (or neither)
				wd = wallsDoorsCheck(level, y, x);
				// Determine what wall to render
				// Straight walls
				if ((!wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && !wd.bottom_door && wd.right_door)
					|| (!wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.top_door && !wd.bottom_door && wd.left_door && !wd.right_door)
					|| (!wd.top_wall && !wd.bottom_wall && wd.right_wall && !wd.top_door && !wd.bottom_door && !wd.left_door && !wd.right_door)
					|| (!wd.top_wall && !wd.bottom_wall && wd.left_wall && !wd.right_wall && !wd.top_door && !wd.bottom_door && !wd.left_door))
					wprintw(room, HORIZONTAL_WALL);
				else if ((!wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.right_wall && wd.bottom_door && !wd.left_door && !wd.right_door)
					|| (!wd.top_wall && !wd.left_wall && !wd.right_wall && wd.top_door && !wd.bottom_door && !wd.left_door && !wd.right_door)
					|| (wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && !wd.bottom_door && !wd.left_door && !wd.right_door)
					|| (wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && !wd.left_door && !wd.right_door))
					wprintw(room, VERTICAL_WALL);
				// Corner walls
				else if ((!wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && wd.bottom_door && !wd.left_door && wd.right_door)
					|| (!wd.top_wall && !wd.bottom_wall && !wd.left_wall && wd.right_wall && !wd.top_door && wd.bottom_door && !wd.left_door && !wd.right_door)
					|| (!wd.top_wall && wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && !wd.bottom_door && !wd.left_door && wd.right_door)
					|| (!wd.top_wall && wd.bottom_wall && !wd.left_wall && wd.right_wall && !wd.top_door && !wd.bottom_door && !wd.left_door && !wd.right_door))
					wprintw(room, TOP_LEFT_WALL);
				else if ((!wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && wd.bottom_door && wd.left_door && !wd.right_door)
					|| (!wd.top_wall && !wd.bottom_wall && wd.left_wall && !wd.right_wall && !wd.top_door && wd.bottom_door && !wd.left_door && !wd.right_door)
					|| (!wd.top_wall && wd.bottom_wall && !wd.left_wall && !wd.right_wall && !wd.top_door && !wd.bottom_door && wd.left_wall && !wd.right_wall)
					|| (!wd.top_wall && wd.bottom_wall && wd.left_wall && !wd.right_wall && !wd.top_door && !wd.bottom_door && !wd.left_wall && !wd.right_wall))
					wprintw(room, TOP_RIGHT_WALL);
				else if (!wd.left_wall && wd.right_wall && wd.top_wall && !wd.bottom_wall)
					wprintw(room, BOTTOM_LEFT_WALL);
				else if (wd.left_wall && !wd.right_wall && wd.top_wall && !wd.bottom_wall)
					wprintw(room, BOTTOM_RIGHT_WALL);
				// Intersecting walls
				else if (!wd.left_wall && wd.right_wall && wd.top_wall && wd.bottom_wall)
					wprintw(room, LEFT_MIDDLE_WALL);
				else if (wd.left_wall && !wd.right_wall && wd.top_wall && wd.bottom_wall)
					wprintw(room, RIGHT_MIDDLE_WALL);
				else if (wd.left_wall && wd.right_wall && !wd.top_wall && wd.bottom_wall)
					wprintw(room, TOP_MIDDLE_WALL);
				else if (wd.bottom_wall && wd.left_wall && wd.right_wall && !wd.top_wall)
					wprintw(room, BOTTOM_MIDDLE_WALL);
				else if ((!wd.top_wall && !wd.bottom_wall && !wd.left_wall && !wd.right_wall && wd.top_door & wd.bottom_door && wd.left_door && wd.right_door)
					|| (!wd.top_wall & !wd.bottom_wall && !wd.left_wall && wd.right_wall && wd.top_door && wd.bottom_door && wd.left_door && !wd.right_door)
					|| (!wd.top_wall & !wd.bottom_wall & wd.left_wall & !wd.right_wall & wd.top_door & wd.bottom_door & !wd.left_door & wd.right_door)
					|| (!wd.top_wall & !wd.bottom_wall & wd.left_wall & wd.right_wall & wd.top_door & wd.bottom_door & !wd.left_door & !wd.right_door)
					|| (!wd.top_wall & wd.bottom_wall & !wd.left_wall & !wd.right_wall & wd.top_door & !wd.bottom_door & wd.left_door & wd.right_door)
					|| (!wd.top_wall & wd.bottom_wall & !wd.left_wall & wd.right_wall & wd.top_door & !wd.bottom_door & wd.left_door & !wd.right_door)
					|| (!wd.top_wall & wd.bottom_wall & wd.left_wall & !wd.right_wall & wd.top_door & !wd.bottom_door & !wd.left_door & wd.right_door)
					|| (!wd.top_wall & wd.bottom_wall & wd.left_wall & wd.right_wall & wd.top_door & !wd.bottom_door & !wd.left_door & !wd.right_door)
					|| (wd.top_wall & !wd.bottom_wall & !wd.left_wall & !wd.right_wall & !wd.top_door & wd.bottom_door & wd.left_door & wd.right_door)
					|| (wd.top_wall & !wd.bottom_wall & !wd.left_wall & wd.right_wall & !wd.top_door & wd.bottom_door & wd.left_door & !wd.right_door)
					|| (wd.top_wall & !wd.bottom_wall & wd.left_wall & !wd.right_wall & !wd.top_door & wd.bottom_door & !wd.left_door & wd.right_door)
					|| (wd.top_wall & !wd.bottom_wall & wd.left_wall & wd.right_wall & !wd.top_door & wd.bottom_door & !wd.left_door & !wd.right_door)
					|| (wd.top_wall & wd.bottom_wall & !wd.left_wall & !wd.right_wall & !wd.top_door & !wd.bottom_door & wd.left_door & wd.right_door)
					|| (wd.top_wall & wd.bottom_wall & !wd.left_wall & wd.right_wall & !wd.top_door & !wd.bottom_door & wd.left_door & !wd.right_door)
					|| (wd.top_wall & wd.bottom_wall & wd.left_wall & !wd.right_wall & !wd.top_door & !wd.bottom_door & !wd.left_door & wd.right_door)
					|| (wd.top_wall & wd.bottom_wall & wd.left_wall & wd.right_wall & !wd.top_door & !wd.bottom_door & !wd.left_door & !wd.right_door))
					wprintw(room, CROSS_WALL);
			}
			// ---------------- END WALLS ----------------
			// ---------------- BEGIN FLOORS ----------------
			else if (level.getMap()[map_index] == '.') {
				wprintw(room, "%c", floor_tiles[rand() % 4]);
			}
			// ---------------- END FLOORS ----------------
			// ---------------- BEGIN DOORS ----------------
			else if (level.getMap()[map_index] == 'D') {
				wprintw(room, LOCKED_DOOR);
			}
			else if (level.getMap()[map_index] == 'd') {
				wd = wallsDoorsCheck(level, y, x);
				if (wd.top_wall && wd.bottom_wall)
					wprintw(room, TOP_OPEN_DOOR);
				else if ((!wd.top_wall && !wd.bottom_wall && wd.left_wall && !wd.right_wall && !wd.left_door && wd.right_door)
					|| (!wd.top_wall && !wd.bottom_wall && wd.left_wall && wd.right_wall && !wd.left_door && !wd.right_door))
					wprintw(room, LEFT_OPEN_DOOR);
				else if ((!wd.top_wall && !wd.bottom_wall && !wd.left_wall && wd.right_wall && wd.left_door && !wd.right_door)
				|| (!wd.top_wall && !wd.bottom_wall && wd.left_wall && wd.right_wall && !wd.left_door && !wd.right_door))
					wprintw(room, RIGHT_OPEN_DOOR);
			}
			// ---------------- END DOORS ----------------
		}
	}

	return room;
}

struct WDBRT LevelRenderer::wallsDoorsCheck(Level level, int win_y, int win_x)
{
	struct WDBRT adjacents;
	// These store the tile in the named direction of this tile
	char top, right, bottom, left;
	// Get the tiles in each direction
	if (win_y != 0)
		top = level.getMap()[(win_y - 1) * level.getWidth() + win_x];
	else top = 0;
	if (win_x != 0)
		left = level.getMap()[win_y * level.getWidth() + (win_x - 1)];
	else left = 0;
	if (win_y != level.getHeight() - 1)
		bottom = level.getMap()[(win_y + 1) * level.getWidth() + win_x];
	else bottom = 0;
	if (win_x != level.getWidth() - 1)
		right = level.getMap()[win_y * level.getWidth() + (win_x + 1)];
	else right = 0;
	// Check if the adjacent tiles are walls
	adjacents.top_wall = (top == '#');
	adjacents.right_wall = (right == '#');
	adjacents.bottom_wall = (bottom == '#');
	adjacents.left_wall = (left == '#');
	// Check if the adjacent tiles are doors
	adjacents.top_door = (top == 'D' || top == 'd');
	adjacents.right_door = (right == 'D' || right == 'd');
	adjacents.bottom_door = (bottom == 'D' || bottom == 'd');
	adjacents.left_door = (left == 'D' || left == 'd');

	return adjacents;
}
