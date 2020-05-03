#include "Agent007.h"

void Agent007::fight(Agent* a, Map& map)
{
	if (this->get_health() <= 0) // daca agentul nu mai are viata, vrem sa-l stergem din vector si de pe harta
	{
		// stergem agentul curent de pe harta
		map.update_map({ this->get_position().first, this->get_position().second }, { a->get_position().first, a->get_position().second }, a->get_name());
		map.remove_agent(this); // stergem agentul din vector

		cout << "	Agent " << this->get_name() << " has died :(... R.I.P\n\n";

		delete this;
	}
	else
	{
		int chance = rand() % 100;
		if (chance > 0 && chance <= 10) // agentul 007 are 10% sansa sa dea one-shot adversarului
		{
			cout << "	Agent " << this->get_name() << " got the divine power and crushed Agent: " << a->get_name() << "\n";
			a->set_health(0);
			this->fight(a, map);
		}
		else
		{
			a->set_health(a->get_health() - this->get_attack()); // ataca adversarul
			if (a->get_health() < 0)
			{
				a->set_health(0);
				cout << "	Agent " << this->get_name() << " attacked " << a->get_name() << " leaving him with: " << a->get_health() << " health\n";
				a->fight(this, map);
			}
			else
			{
				cout << "	Agent " << this->get_name() << " attacked " << a->get_name() << " leaving him with: " << a->get_health() << " health\n";
				a->fight(this, map);
			}
		}
	}
}