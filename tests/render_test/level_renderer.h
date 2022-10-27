#ifndef LEVEL_RENDERER_H_
#define LEVEL_RENDERER_H_

#include <ncurses.h>
#include "WDBRT.h"
#include "level.h"

class LevelRenderer
{
	struct WDBRT wallsDoorsCheck(Level, int win_y, int win_x);
public:
	WINDOW* renderLevel(Level);	
};

#endif

