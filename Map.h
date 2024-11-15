#pragma once
#include "Platform.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
class Map
{
	sf::Texture backgroundLayerTexture;
	sf::Texture foregroundLayerTexture;
	sf::Sprite backgroundLayer;
	sf::Sprite foregroundLayer;
	std::vector<Platform> platforms;

public:

	Map();
	void loadMap();
	void update(float positionX);
	void checkCollision(Character charactor);
	void render(sf::RenderWindow& window, sf::View& view);
};



