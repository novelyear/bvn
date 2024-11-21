#pragma once
#include "Character.h"
class Gaara :
    public Character {
public:


	Gaara();
	Gaara(int flag);

	void takeDamage(int amount) override;
	void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) override;
	void useSkill() override;
};

