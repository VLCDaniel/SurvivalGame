#pragma once
#include "Agent.h"
class AgentTank :
	public Agent
{
public:
	AgentTank(int posx = -1, int posy = -1, unsigned r = 4, unsigned h = 250, unsigned a = 25, string n = "T") : Agent(posx, posy, r, h, a, n) {};
	void fight(Agent*, Map&) override;

	~AgentTank() {};
};

