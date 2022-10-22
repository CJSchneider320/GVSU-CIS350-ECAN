#ifndef LEVEL_RENDERER_H_
#define LEVEL_RENDERER_H_

#include <ncurses.h>
#include "level.h"

class LevelRenderer
{
public:
	WINDOW* renderLevel(Level);	
};

#endif

