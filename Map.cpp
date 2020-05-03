#include <iostream>
#include "Map.h"

Map::Map(const unsigned row, const unsigned col): rows(row), columns(col)
{
	map.resize(row);
	for (unsigned int i = 0; i < row; i++)
	{
		map[i].resize(col, " ");
	}
}

void Map::add_agent(Agent* a)
{
	this->agents.push_back(a);
}

unsigned Map::get_rows() const
{
	return this->rows;
}

unsigned Map::get_columns() const
{
	return this->columns;
}

bool Map::is_agent(unsigned row, unsigned col) const
{
	return this->map[row][col] == " ";
}

void Map::insert_agent(Agent* a, string s)
{
	this->map[a->get_position().first][a->get_position().second] = s;
}

void Map::display_map() const
{
	for (unsigned i = 0; i < this->rows; i++)
	{
		cout << (char)186 << ' ';
		for (unsigned j = 0; j < this->columns; j++)
		{
			cout << this->map[i][j] << ' ';
		}
		cout << (char)186;
		cout << '\n';
	}
}

vector<Agent*> Map::get_agents() const
{
	return this->agents;
}

void Map::update_map(pair<int, int> old_pos, pair<int, int> new_pos, string s)
{
	this->map[old_pos.first][old_pos.second] = " ";
	this->map[new_pos.first][new_pos.second] = s;
}

void Map::remove_agent(Agent* a)
{
	for (int i = 0; i < this->agents.size(); i++)
	{
		if (a == this->agents[i])
		{
			this->agents.erase(this->agents.begin() + i);
		}
	}
}

ostream& operator<< (ostream& out, const Map& map)
{
	out << (char)201;
	unsigned row = map.get_rows();
	unsigned col = map.get_columns();

	for (unsigned i = 0; i < 2 * col + 1; i++)
	{
		out << (char)205;
	}
	out << (char)187;
	out << '\n';

	map.display_map();

	out << (char)200;
	for (unsigned int i = 0; i < 2 * col + 1; i++)
	{
		out << (char)205;
	}

	out << (char)188 << '\n';

	return out;
}