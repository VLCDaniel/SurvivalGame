#pragma once
#include <iostream>
#include <utility>
#include "Map.h"
using namespace std;

class Map;
class Agent
{
private: // imi usuram putin munca daca le faceam protected, dar mi-am dat seama prea tarziu
	static unsigned NumberOfAgents;
	pair<int, int> position;
	int health;
	const unsigned range;
	const unsigned attack;
	const string name;

	void move_towards_center(unsigned, unsigned, unsigned, unsigned, Map&);
	void find_enemy(pair<int, int>, unsigned, unsigned);

public:
	Agent(int row = -1, int col = -1, unsigned r = 1, unsigned h = 100, unsigned a = 25, string n = "A") : position({ row, col }), range(r), health(h), attack(a), name(n) { this->NumberOfAgents++; };
	
	void spawn_agent(Map&);

	// getteri 
	pair<int, int> get_position() const { return this->position; };
	int get_health() const { return this->health; }
	unsigned get_attack() const { return this->attack; };
	string get_name() const { return this->name; };
	string get_name() { return this->name; };
	static unsigned get_agents_alive();
	void set_health(int h) { this->health = h; };

	pair<int, int> search(Map&); // search for closest agent
	void move(pair<int, int>, Map&);
	virtual void fight(Agent*, Map&) = 0;

	virtual ~Agent() { this->NumberOfAgents--;};
};