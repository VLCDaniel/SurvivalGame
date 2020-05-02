#include<math.h>
#include "Agent.h"

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

void Agent::move(pair<int, int> pos, Map& map)
{
	unsigned row = map.get_rows();
	unsigned col = map.get_columns();
	if (pos.first == -1 && pos.second == -1) // daca nu exista agenti pe langa agentul actual, vreau sa mut agentul actual catre centrul hartii
	{
		int old_row = this->position.first;
		int old_col = this->position.second;
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
	}
	else
	{
		int old_row = this->position.first;
		int old_col = this->position.second;
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
		map.update_map({ old_row, old_col }, { this->position.first, this->position.second }, this->name);
	}
}