#include <iostream>
#include "Map.h"

Map::Map(const unsigned row, const unsigned col): rows(row), columns(col)
{
	map.resize(row + 1);
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

bool Map::get_agent(unsigned row, unsigned col) const
{
	return this->map[row][col] == " ";
}

void Map::insert_agent(Agent* a, string s)
{
	this->map[a->position.first][a->position.second] = s;
}

void Map::display_map() const
{
	char c = 186;

	for (unsigned i = 0; i < this->rows; i++)
	{
		cout << c << ' ';
		for (int j = 0; j < this->columns; j++)
		{
			cout << this->map[i][j] << ' ';
		}
		cout << c;
		cout << '\n';
	}
}

ostream& operator<< (ostream& out, const Map& map)
{
	char c = 201;
	out << c;
	c = 205;
	unsigned row = map.get_rows();
	unsigned col = map.get_columns();

	for (unsigned i = 0; i < 2 * col + 1; i++)
	{
		out << c;
	}
	c = 187;
	out << c;
	out << '\n';

	map.display_map();

	c = 200;
	out << c;
	c = 205;
	for (unsigned int i = 0; i < 2 * col + 1; i++)
	{
		out << c;
	}

	c = 188;
	out << c << '\n';

	return out;
}