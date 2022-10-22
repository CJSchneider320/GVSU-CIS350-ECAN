#include <ncurses.h>
#include <string>
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
	map += "####################";
	map += "#......#.....#.....#";
	map += "#......#############";
	map += "#......#.....#.....#";
	map += "#......#######.....#";
	map += "#......#..........##";
	map += "#..................#";
	map += "#..............#...#";
	map += "#...#####......#####";
	map += "#...#..........#...#";
	map += "#...#..........#####";
	map += "#...########...#...#";
	map += "#...#...#..#...#...#";
	map += "#...#...#..#...#...#";
	map += "####################";
	
	// map is: height = 14, width = 20

	Level test_level(15, 20, map);

	assert(test_level.getHeight() == 15);
	assert(test_level.getWidth() == 20);
	assert(test_level.getMap() == map);
	
	setlocale(LC_ALL, "");
	initscr();
	
	WINDOW* room = renderer.renderLevel(test_level);
	refresh();
	wrefresh(room);
	getch();
	endwin();
}

