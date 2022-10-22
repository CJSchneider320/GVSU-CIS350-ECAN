#include <string>
#include "level.h"

using namespace std;

Level::Level(int h, int w, string m)
{
	height = h;
	width = w;
	map = m;
}

string Level::getMap()
{
	return map;
}

int Level::getHeight()
{
	return height;
}

int Level::getWidth()
{
	return width;
}

