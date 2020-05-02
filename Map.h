#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Agent.h"
using namespace std;

class Agent;
class Map
{
private:
	vector<vector<string>> map;
	vector<Agent*> agents;
	const unsigned rows;
	const unsigned columns;
public:
	Map(const unsigned, const unsigned);
	//virtual ~Map();

	void add_agent(Agent*); // adaugam agenti in vector
	unsigned get_rows() const;
	unsigned get_columns() const;
	bool is_agent(unsigned, unsigned) const; // verificam daca se afla un agent pe pozitia data
	void insert_agent(Agent*, string); // adaugam un agent in matrice
	void update_map(pair<int, int>, pair<int, int>, string); // actualizam harta in fiecare runda
	void display_map() const;
	vector<Agent*> get_agents();
	friend ostream& operator<<(ostream&, const Map&);
};

