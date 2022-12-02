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
	map += "#.....#........D.......................#";
	map += "#.....#........#......!!...............#";
	map += "#R....#........#....R..........r.......#";
	map += "#########!!!!####...v..!!.....#.......p#";
	map += "#.........^^...#....v.........#....#####";
	map += "#.........^^...#....v.!!......#....d..L#";
	map += "#....>>>>>^^...#....v.........#....d...#";
	map += "#..........^...####.v.!!...#########...#";
	map += "#..........^<<<<<<<<<.........#...D....#";
	map += "#.............................#...##DD##";
	map += "#...#!!!!!!#......................#....#";
	map += "#.@.#......#..........#D#.........#..P.#";
	map += "#.s.#......#..........#S#.........#r...#";
	map += "########################################";
	
	// map is: height = 15, width = 40

	Level test_level(15, 40, map);

	assert(test_level.getHeight() == 15);
	assert(test_level.getWidth() == 40);
	assert(test_level.getMap() == map);
	
	setlocale(LC_ALL, "");
	initscr();
	
	if (!has_colors()) {
		printw("This terminal does not support color.");
		mvprintw(1, 0, "Please use a terminal that does support color.");
		getch();
		return -1;
	}

	start_color();

	WINDOW* room = renderer.renderLevel(test_level);
	refresh();
	wrefresh(room);
	getch();
	endwin();
}

