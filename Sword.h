#pragma once
#include "Item.h"
class Sword :
	public Item
{
public:
	Sword() : Item(0, 15, "Excalibur") {};
	void add_status(Agent* a) override { a->set_attack(a->get_attack() + this->get_damage()); };

	~Sword() {};
};

