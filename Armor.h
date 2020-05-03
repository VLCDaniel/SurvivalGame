#pragma once
#include "Item.h"
class Armor :
	public Item
{
public:
	Armor() : Item(50, 0, "Great Helmet") {};
	void add_status(Agent* a) override { a->set_health(a->get_health() + this->get_health()); };

	~Armor() {};
};

