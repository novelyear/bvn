#pragma once
#include "Character.h"
class Gaara :
    public Character {
public:
	Gaara();


	void loadImage() override; // º”‘ÿÕº∆¨
	void takeDamage(int amount) override;
	void update(float deltaTime) override;
	void handleMove() override;
	void handleInput(sf::Event event) override;
	void useSkill() override;
};

