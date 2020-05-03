#include<math.h>
#include "Agent.h"
#include "Armor.h"
#include "Sword.h"
#include "Socks.h"
#include "Gloves.h"

unsigned Agent::NumberOfAgents = 0;

unsigned Agent::get_agents_alive()
{
	return Agent::NumberOfAgents;
}

void Agent::spawn_agent(Map& map) // generez random pozitia agentilor si ii inserez intr-un vector
{
	unsigned row = map.get_rows();
	unsigned col = map.get_columns();

	unsigned randrow = rand() % row;
	unsigned randcol = rand() % col;
	while (map.is_agent(randrow, randcol) == false)
	{
		randrow = rand() % row;
		randcol = rand() % col;
	}
	this->position.first = randrow;
	this->position.second = randcol;

	int x = rand() % 4; // generez un item random pentru fiecare agent
	if (x == 0)
	{
		this->item = new Armor;
		item->add_status(this);
	}
	if (x == 1)
	{
		this->item = new Sword;
		item->add_status(this);
	}
	if (x == 2)
	{
		this->item = new Socks;
		item->add_status(this);
	}
	if (x == 3)
	{
		this->item = new Gloves;
		item->add_status(this);
	}

	cout << "Agent " << this->name << " has gotten: " << this->item->get_item_name() << " as his item. Good luck to battle!\n\n";
	map.add_agent(this);
	map.insert_agent(this, this->get_name());
}

pair<int, int> Agent::search(Map& m)
{
	pair<int, int> pos = { -1, -1 };
	int ok = 0; // presupunem ca nu gasim nimic in raza agentului
	pair<int, int> currentposition = this->position;
	
	/// Generam aria de viziune a agentului
	unsigned top;
	if ((int)this->range > currentposition.first) top = 0;
	else top = currentposition.first - this->range;

	unsigned bottom = currentposition.first + this->range;
	if (bottom >= m.get_rows())bottom = m.get_rows() - 1;

	unsigned left;
	if ((int)this->range > currentposition.second) left = 0;
	else left = currentposition.second - this->range;

	unsigned right = currentposition.second + this->range;
	if (right >= m.get_columns()) right = m.get_columns() - 1;

	// cautam agentul care se afla la distanta minima de agentul curent(daca exista)
	unsigned dist = this->range; // o sa se afle la distanta maxima range

	// formula: max( abs( currentposition.first - i), abs( currentposition.second - j) )
	for (unsigned i = top; i <= bottom; i++)
	{
		for (unsigned j = left; j <= right; j++)
		{
			if (m.is_agent(i, j) == false && (i != currentposition.first || j != currentposition.second)) // exista agent la pozitia [i, j] 
			{
				unsigned aux;
				if (abs(int(currentposition.first) - int(i)) > abs(int(currentposition.second) - int(j)))
				{
					aux = abs(int(currentposition.first) - int(i));
					if (aux < dist)
					{
						dist = aux;
						pos = { i, j };
					}
				}
				else
				{
					aux = abs(int(currentposition.second) - int(j));
					if (aux < dist)
					{
						dist = aux;
						pos = { i, j };
					}
				}
			}
		}
	}
	return pos;
}

void Agent::move_towards_center(unsigned row, unsigned col, unsigned old_row, unsigned old_col, Map& map)
{
	if (this->position.first > (int)row / 2) // a doua jumatate(partea de jos)
	{
		if (this->position.second < (int)col / 2) // partea din stanga
		{
			this->position.first -= 1;
			this->position.second += 1;
		}
		else if (this->position.second > (int)col / 2) // partea din dreapta
		{
			this->position.first -= 1;
			this->position.second -= 1;
		}
		else // coloana din mijloc
		{
			this->position.first -= 1;
		}
	}

	if (this->position.first < (int)row / 2) // prima jumatate(partea de sus)
	{
		if (this->position.second < (int)col / 2) // partea din stanga
		{
			this->position.first += 1;
			this->position.second += 1;
		}
		else if (this->position.second > (int)col / 2) // partea din dreapta
		{
			this->position.first += 1;
			this->position.second -= 1;
		}
		else // coloana din mijloc
		{
			this->position.first += 1;
		}
	}

	if (this->position.first == row / 2) // linia din mijloc
	{
		if (this->position.second < (int)col / 2) // partea din stanga
		{
			this->position.second += 1;
		}
		if (this->position.second > (int)col / 2) // partea din dreapta
		{
			this->position.second -= 1;
		}
	}
	map.update_map({ old_row, old_col }, { this->position.first, this->position.second }, this->name);
	cout << "Agent: " << this->name << " moved from: (" << old_row << "," << old_col << ") to: (";
	cout << this->position.first << ',' << this->position.second << ")\n\n";
}

void Agent::find_enemy(pair<int, int> pos, unsigned old_row, unsigned old_col)
{
	if (this->position.first > pos.first) // deasupra(partea de sus)
	{
		if (this->position.second < pos.second) // partea din stanga
		{
			this->position.first -= 1;
			this->position.second += 1;
		}
		else if (this->position.second > pos.second) // partea din dreapta
		{
			this->position.first -= 1;
			this->position.second -= 1;
		}
		else // se afla pe aceeasi coloana
		{
			this->position.first -= 1;
		}
	}

	if (this->position.first < pos.first) // dedesubt
	{
		if (this->position.second < pos.second) // partea din stanga
		{
			this->position.first += 1;
			this->position.second += 1;
		}
		else if (this->position.second > pos.second) // partea din dreapta
		{
			this->position.first += 1;
			this->position.second -= 1;
		}
		else // aceeasi coloana
		{
			this->position.first += 1;
		}
	}

	if (this->position.first == pos.first) // aceeasi linie
	{
		if (this->position.second < pos.second) // partea din stanga
		{
			this->position.second += 1;
		}
		if (this->position.second > pos.second) // partea din dreapta
		{
			this->position.second -= 1;
		}
	}
	cout << "Agent: " << this->name << " moved from: (" << old_row << "," << old_col << ") to: (";
	cout << this->position.first << ',' << this->position.second << ")\n\n";
}

void Agent::move(pair<int, int> pos, Map& map)
{
	unsigned row = map.get_rows();
	unsigned col = map.get_columns();

	int old_row = this->position.first;
	int old_col = this->position.second;

	if (pos.first == -1 && pos.second == -1) // daca nu exista agenti pe langa agentul actual, vreau sa mut agentul actual catre centrul hartii
	{
		this->move_towards_center(row, col, old_row, old_col, map);
	}
	else // altfel, a gasit un agent in aria lui de viziune si se indreapta catre el
	{
		this->find_enemy(pos, old_row, old_col);

		if (this->position == pos) // daca se afla pe aceeasi pozitie, incepe lupta
		{
			for (Agent* i : map.get_agents()) // parcurg vectorul de agenti
			{
				if (i->position == pos && i != this) // daca am gasit agentul care se afla pe pozitia pos, apelez functia fight
				{
					map.update_map({ old_row, old_col }, { this->position.first, this->position.second }, i->name);
					int ban = rand() % 2; // dam cu banul: 1 - cap, 0 - pajura
					if (ban % 2 == 1) // cap - agentul curent ataca primul
					{
						this->fight(i, map);
					}
					else
					{
						i->fight(this, map); // pajura - agentul gasit ataca primul
					}
					break;
				}
			}
		}
		else
		{
			map.update_map({ old_row, old_col }, { this->position.first, this->position.second }, this->name);
		}
	}
}