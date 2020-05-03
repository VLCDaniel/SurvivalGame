#include "AgentFighter.h"

void AgentFighter::fight(Agent* a, Map& map)
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
		if (chance > 0 && chance <= 20) // agentul Tank are 20% sansa sa dea crit
		{
			a->set_health(a->get_health() - int(this->get_attack() * 1.5));

			if (a->get_health() < 0)
			{
				a->set_health(0);
				cout << "	Agent " << this->get_name() << " got lucky and dealt " << this->get_attack() * 1.5 << " damage to " << a->get_name() << "leaving him with " << a->get_health() << " health\n";
				a->fight(this, map);
			}
			else
			{
				cout << "	Agent " << this->get_name() << " got lucky and dealt " << this->get_attack() * 1.5 << " damage to " << a->get_name() << " leaving him with " << a->get_health() << " health\n";
				a->fight(this, map);
			}
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