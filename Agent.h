#pragma once
#include <iostream>
#include <utility>
#include "Map.h"
using namespace std;

class Map;
class Agent
{
public:
	pair<int, int> position;
	int health;
	unsigned range;
	unsigned attack;
	string name;
public:
	Agent(int row = -1, int col = -1, unsigned r = 1, unsigned h = 100, unsigned a = 25, string n = "A") : position({ row, col }), range(r), health(h), attack(a), name(n) {};
	pair<int, int> search(Map&); // search for closest agent
	void move(pair<int, int>, Map&);
	virtual void foo() = 0;
	string get_name() { return this->name; };
};