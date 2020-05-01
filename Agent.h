#pragma once
#include <iostream>
#include <utility>
using namespace std;

class Agent
{
public:
	pair<int, int> position;
	int health;
	unsigned range;
	unsigned attack;
public:
	Agent(int row = -1, int col = -1, unsigned r = 1, unsigned h = 100, unsigned a = 25) : position({ row, col }), range(r), health(h), attack(a) {};
	virtual void foo() = 0;
};