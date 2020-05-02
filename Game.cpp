#include <ctime>
#include "Game.h"
#include "AgentTank.h"
#include "AgentFighter.h"
#include "Agent007.h"

unsigned Game::rounds = 0;

Game::Game()
{
	cout << "Initializing game..." << '\n';
	this->map = NULL;
}

void Game::start_game()
{
	srand(time(NULL));

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

		for (unsigned i = 1; i <= ag; i++) // generez random pozitia agentilor si ii inserez intr-un vector
		{
			Agent* a;
			unsigned randrow = rand() % row; // Agent Tank
			unsigned randcol = rand() % col;
			while (map->is_agent(randrow, randcol) == false)
			{
				randrow = rand() % row;
				randcol = rand() % col;
			}
			a = new AgentTank(randrow, randcol);
			map->add_agent(a);
			map->insert_agent(a, a->get_name());

			randrow = rand() % row; // Agent Fighter
			randcol = rand() % col;
			while (map->is_agent(randrow, randcol) == false)
			{
				randrow = rand() % row;
				randcol = rand() % col;
			}
			a = new AgentFighter(randrow, randcol);
			map->add_agent(a);
			map->insert_agent(a, a->get_name());

			randrow = rand() % row; // Agent 007
			randcol = rand() % col;
			while (map->is_agent(randrow, randcol) == false)
			{
				randrow = rand() % row;
				randcol = rand() % col;
			}
			a = new Agent007(randrow, randcol);
			map->add_agent(a);
			map->insert_agent(a, a->get_name());
		}

	char cont = 'y';
	vector<Agent*> ags = map->get_agents();
	do // in fiecare runda
	{
		cout << "Round: " << this->rounds << '\n';
		this->rounds++;
		cout << *map;
		cout << '\n' << "Continue? n - No, y - Yes: ";
		cin >> cont;

		for (int i = 0; i < ags.size(); i++) // pentru fiecare agent
		{
			pair<unsigned, unsigned> current_position = ags[i]->position; // pozitia agentului curent
			pair<int, int> closest_agent;
			closest_agent = ags[i]->search(*map); // cautam cel mai apropiat agent(daca exista) din range-ul lui
			ags[i]->move(closest_agent, *map);
		}
		cout << '\n';
		if (cont != 'n' && cont != 'y')
		{
			cont = 'n';
		}
	} while (cont == 'y');
}

Game::~Game()
{
	this->rounds = 0;
	delete map;
	cout << "Game is stopping..." << '\n';
}