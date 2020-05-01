#include <ctime>
#include "Game.h"
#include "AgentTank.h"

unsigned Game::rounds = 0;

Game::Game()
{
	srand(time(NULL));
	cout << "Initializing game..." << '\n';

	unsigned row;
	do
	{
		cout << "Map Length(Min 15): ";
		cin >> row;
	} while (row < 15);

	unsigned col;
	do
	{
		cout << "Map Width(Min 15): ";
		cin >> col;
	} while (col < 15);

	unsigned ag;
	do
	{
		cout << "Number of agents for every type(Min 7): ";
		cin >> ag;
	} while (ag < 7);

	map = new Map(row, col);

	for (unsigned i = 1; i <= ag; i++)
	{
		Agent* a;
		unsigned randrow = rand() % row;
		unsigned randcol = rand() % col;
		while (map->get_agent(randrow, randcol)==false)
		{
			randrow = rand() % row;
			randcol = rand() % col;
		}
		a = new AgentTank(randrow, randcol);
		map->add_agent(a);
		map->insert_agent(a, "a");
	}

	char cont = 'y';
	do
	{
		this->rounds++;
		cout << "Round: " << this->rounds << '\n';
		cout << *map; 
		cout << '\n' << "Continue? n - No, y - Yes: ";
		cin >> cont;
		cout << '\n';
		if (cont !='n' && cont != 'y')
		{
			cont = 'n';
		}
	} while (cont == 'y');
	cout << "Game stopping..." << '\n';
}

Game::~Game()
{
	this->rounds = 0;
	delete map;
}