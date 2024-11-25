#pragma once
#include "Character.h"
class Gaara :
    public Character {
public:
	Gaara();
	Gaara(int flag);


	void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) override;
	void loadResources(const std::string& directory, const std::string& rangeFile,
	const std::string& originFile, const std::string& anchorFile) override;
	void handleMove() override;
	void updateSprite(float deltaTime) override;
};

