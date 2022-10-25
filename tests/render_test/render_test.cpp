#include <iostream>
#include <locale>
#include <cassert>
#include "level.h"
#include "level_renderer.h"
using namespace std;

int main(int argc, char** argv)
{
	LevelRenderer renderer;
	string map;
	map += "########################################";
	map += "#....P.#     #l....d...................#";
	map += "#......#     #######...................#";
	map += "#R.....#     #.........................#";
	map += "##############!!.....>>v......#........#";
	map += "#......#.......!.....^<<.....B#.......##";
	map += "#..............!............###........#";
	map += "#..............#............# #........#";
	map += "#...#####......####!!!!!!!!######......#";
	map += "#...#..........D..............#........#";
	map += "#...#..........####...........#...######";
	map += "#...##d#####...#..................#....#";
	map += "#.@.#...#  #...#......#D#.........#..P.#";
	map += "#.s.#.c.#  #..L#......#S#.........#r...#";
	map += "########################################";
	
	// map is: height = 15, width = 40

	Level test_level(15, 40, map);

	assert(test_level.getHeight() == 15);
	assert(test_level.getWidth() == 40);
	assert(test_level.getMap() == map);
	
	setlocale(LC_ALL, "");
	initscr();
	
	WINDOW* room = renderer.renderLevel(test_level);
	refresh();
	wrefresh(room);
	getch();
	endwin();
}

