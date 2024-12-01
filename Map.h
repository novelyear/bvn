#pragma once
#include <SFML/Graphics.hpp>
enum class MapType {
	MR
};

class Platform
{
public:
	sf::Vector2f startPosition;
	float width;
	Platform(sf::Vector2f startPosition, float width);
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

class MR : public Map {
public:
	MR();
	void loadMap() override;
	void loadPlatform() override;
};




