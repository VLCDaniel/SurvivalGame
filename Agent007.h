#pragma once
#include "Agent.h"
class Agent007 :
	public Agent
{
public:
	Agent007(int posx = -1, int posy = -1, unsigned r = 5, unsigned h = 100, unsigned a = 30, string n = "7") : Agent(posx, posy, r, h, a, n) {};
	void fight(Agent*, Map&) override;

	~Agent007() {};
};

