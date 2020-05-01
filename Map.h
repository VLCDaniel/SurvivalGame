#pragma once
#include <iostream>
#include "Agent.h"
#include <vector>
#include <string>
using namespace std;

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

	void add_agent(Agent*);
	unsigned get_rows() const;
	unsigned get_columns() const;
	bool get_agent(unsigned, unsigned) const;
	void insert_agent(Agent*, string);
	void display_map() const;
	friend ostream& operator<<(ostream&, const Map&);
};

