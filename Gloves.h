#pragma once
#include "Item.h"
class Gloves :
	public Item
{
public:
	Gloves() : Item(-40, 20, "Modern Gauntlets") {};
	void add_status(Agent* a) override {
		a->set_attack(a->get_attack() + this->get_damage());
		a->set_health(a->get_health() + this->get_health());
	};

	~Gloves() {};
};

