#pragma once
#include "Agent.h"
using namespace std;

class Agent;
class Item
{
private:
	int health;
	int damage;
	string name;
public:
	Item(int h = 0, int d = 0, string n = "") : health(h), damage(d), name(n) {};
	virtual void add_status(Agent *) = 0;

	int get_health() const { return this->health; };
	int get_damage() const { return this->damage; };
	string get_item_name() const { return this->name; };
	virtual ~Item() {};
};

