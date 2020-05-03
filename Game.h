#pragma once
#include "Map.h"

class Game
{
private:
	Map* map;
	static unsigned rounds;
public:
	Game() : map(NULL) { cout << "Initializing game...\n"; };
	void start_game();
	~Game();
};

