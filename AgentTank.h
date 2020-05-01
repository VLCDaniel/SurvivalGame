#pragma once
#include "Agent.h"
class AgentTank :
	public Agent
{
public:
	AgentTank(int posx = -1, int posy = -1, unsigned r = 4, unsigned h = 250) : Agent(posx, posy, r, h) {};
	void foo() override {};
};
