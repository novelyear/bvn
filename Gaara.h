#pragma once
#include "Character.h"
class Gaara :
    public Character {
public:
	Gaara();
	Gaara(int flag);

	void updateSprite(float deltaTime) override;
	void loadImage() override; // º”‘ÿÕº∆¨
	void takeDamage(int amount) override;
	void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) override;
	void useSkill() override;
};

