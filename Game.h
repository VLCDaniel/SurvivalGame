#pragma once
#include "Map.h"

class Game
{
private:
	Map* map;
	static unsigned rounds;
public:
	Game();
	~Game();
};

