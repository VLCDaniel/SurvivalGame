#pragma once
#include "Item.h"
class Socks :
	public Item
{
public:
	Socks() : Item(15, 5, "Silver Socks") {};
	void add_status(Agent* a) override { a->set_attack(a->get_attack() + this->get_damage());
										 a->set_health(a->get_health() + this->get_health());};

	~Socks() {};
};

