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
	void exertEffect(Character* enemy, Effect * e) override;
	void exertEffect(Character* enemy) override;
};