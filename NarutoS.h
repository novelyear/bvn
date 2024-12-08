#pragma once
#include "Character.h"
class Effect;

class NarutoS :
    public Character {
public:
	NarutoS();
	NarutoS(int flag);

	bool canTouch() override;
	void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) override;
	void loadResources(const std::string& directory, const std::string& rangeFile,
		const std::string& originFile, const std::string& anchorFile) override;
	void handleMove() override;
	void updateSprite(float deltaTime, sf::Vector2f enemyPosition) override;
	void updateCollisionWithEnemy(Character* enemy) override;
	void exertEffect(Character* enemy, Effect * e) override;
	void exertEffect(Character* enemy) override;

	void ku() override;
	void u() override;
};

class NarutoSEffect : 
	public Effect {
public:

	NarutoSEffect();

	void ki(sf::Vector2f position, bool left) override;

	void updatePosition(sf::View view) override;
	void updateSprite(float deltaTime) override;
};