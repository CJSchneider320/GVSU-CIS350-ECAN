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
	map += "####################################################";
	map += "#                                                  #";
	map += "# #D# ## ## ## ## #  #   #  # #D# #d#   #   #   #  #";
	map += "#      D  d D  d  D  d   D  d   #   # #D##  D  ### #";
	map += "# # #  #  # #  #  ## ## ## ##           #  ###  d  #";
	map += "# D d                         #D# #d#       #   #  #";
	map += "# # #  ### ###  #   #    #    #   #     #          #";
	map += "#       D   d   D   d  #D##           #d##  #   #  #";
	map += "# #d#   #   #  ### ###          #   #   #   d   D  #";
	map += "#                        #    #D# #d#      ###  D  #";
	map += "# #D## #d## ##D# ##d#  #d##            #    #   #  #";
	map += "#   #    #   #    #           #   #   ##D#         #";
	map += "#                       #     #D# #d#  #    #   #  #";
	map += "# #  #  #  #   #  #    ##D#                ###  d  #";
	map += "# ## ## D  d  ## ##           #  #     #    D   d  #";
	map += "# D  d  ## ##  D  d     #     D  d    ##d#  #   #  #";
	map += "# #  #  #  #   #  #    ##d#  ## ##     #           #";
	map += "#                             #  #  #    ###########";
	map += "# #   #     #   # ###########         ####          ";
	map += "# #D# #d# #D# #d# #         ###########             ";
	map += "# #   #     #   # #                                 ";
	map += "#                 #                                 ";
	map += "# #dd# #DD# #######                                 ";
	map += "#           #                                       ";
	map += "#############                                       ";
	
	// map is: height = 25, width = 52

	Level test_level(25, 52, map);

	assert(test_level.getHeight() == 25);
	assert(test_level.getWidth() == 52);
	assert(test_level.getMap() == map);
	
	setlocale(LC_ALL, "");
	initscr();
	
	WINDOW* room = renderer.renderLevel(test_level);
	refresh();
	wrefresh(room);
	getch();
	endwin();

}

