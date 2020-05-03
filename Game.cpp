#include <ctime>
#include "Game.h"
#include "AgentTank.h"
#include "AgentFighter.h"
#include "Agent007.h"

unsigned Game::rounds = 0;

void Game::start_game()
{
	srand(time(NULL)); // pentru functia rand()

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
	cout << '\n';

	map = new Map(row, col); // creez mapa

	Agent* a;
	for (unsigned i = 1; i <= ag; i++) // spawnez agentii pe harta
	{
		a = new AgentTank;
		a->spawn_agent(*map);

		a = new AgentFighter;
		a->spawn_agent(*map);

		a = new Agent007;
		a->spawn_agent(*map);
	}

	char cont = 'y';
	do // in fiecare runda
	{
		if (Agent::get_agents_alive() == 1)
		{
			cout << *map;
			cout << "This game took " << this->rounds << " rounds.\n";
			cout << map->get_agents()[0]->get_name() << " killed everyone and won the game! Congrats! :D\n";
		}
		else
		{
			cout << "Round: " << this->rounds << " - Agents alive: " << Agent::get_agents_alive() << '\n';
			this->rounds++;
			cout << *map;
			cout << '\n' << "Continue? n - No, y - Yes: ";
			cin >> cont;
			cout << '\n';
		}

		if (cont != 'n' && cont != 'y' || Agent::get_agents_alive() == 1)
		{
			cont = 'n';
		}
		else
		{
			for (int i = 0; i < map->get_agents().size(); i++) // pentru fiecare agent
			{
				pair<unsigned, unsigned> current_position = map->get_agents()[i]->get_position(); // pozitia agentului curent
				pair<int, int> closest_agent;
				closest_agent = map->get_agents()[i]->search(*map); // cautam cel mai apropiat agent(daca exista) din range-ul lui
				map->get_agents()[i]->move(closest_agent, *map); // mutam agentul catre pozitia respectiva si initializam lupta(daca e cazul)
			}
		}
	} while (cont == 'y');
}

Game::~Game()
{
	this->rounds = 0;
	delete map;
	cout << "Game is stopping..." << '\n';
}