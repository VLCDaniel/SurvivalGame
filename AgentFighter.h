#pragma once
#include "Agent.h"
class AgentFighter :
	public Agent
{
public:
	AgentFighter(int posx = -1, int posy = -1, unsigned r = 3, unsigned h = 150, unsigned a = 50, string n = "F") : Agent(posx, posy, r, h, a, n) {};
	void fight(Agent*, Map&) override;

	~AgentFighter() {};
};

