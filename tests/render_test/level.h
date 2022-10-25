#ifndef LEVEL_H
#define LEVEL_H

#include <string>

using namespace std;

class Level
{
	string map;
	int height;
	int width;

public:
	Level(int height, int width, string map);
	string getMap();
	int getHeight();
	int getWidth();
};

#endif
