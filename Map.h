#pragma once
#include "Platform.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
enum class MapType {
	MR
};

class Map {
public:
	sf::Texture backgroundLayerTexture;
	sf::Texture foregroundLayerTexture;
	sf::Sprite backgroundLayer;
	sf::Sprite foregroundLayer;
	std::vector<Platform> platforms;

	Map();
	virtual void loadMap() = 0;
	virtual void loadPlatform() = 0;
	void render(sf::RenderWindow& window, sf::View& view);
};



