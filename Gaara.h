#pragma once
#include "Character.h"
class Gaara :
    public Character {
public:


	Gaara();
	Gaara(int flag);

	void takeDamage(int amount) override;
};

