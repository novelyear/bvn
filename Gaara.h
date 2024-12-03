#pragma once
#include "Character.h"
class Gaara :
    public Character {

public:

	Gaara();
	Gaara(int flag);

	bool canTouch() override;
	void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) override;
	void loadResources(const std::string& directory, const std::string& rangeFile,
	const std::string& originFile, const std::string& anchorFile) override;
	void handleMove() override;
	void updateSprite(float deltaTime, sf::Vector2f enemyPosition) override;
	void exertEffect(Character* enemy, int type) override;

	void wu() override;
	void u() override;
	void ku() override;
	void si() override;
	void i() override;

};

class GaaraEffect :
	public Effect {
public:

	GaaraEffect();

	void u(sf::Vector2f position, bool left)override;
	void wu(sf::Vector2f position) override;
	void si_before(sf::Vector2f position) override;
	void si_after(sf::Vector2f position) override;
	void i_before(sf::Vector2f position) override;


	void updatePosition(sf::View view) override;
	void updateSprite(float deltaTime) override;
};