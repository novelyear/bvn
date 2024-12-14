#pragma once
#include <SFML/Graphics.hpp>
enum class MapType {
	MR, VE
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
	static float LEFT_BORDER;
	static float RIGHT_BORDER;
	static float GROUND;
	static float CHARACTER_BOTTOM;

	sf::Texture backgroundLayerTexture;
	sf::Texture foregroundLayerTexture;
	sf::Sprite backgroundLayer;
	sf::Sprite foregroundLayer;
	std::vector<Platform> platforms;

	Map();
	virtual void loadMap() = 0;
	virtual void loadPlatform() = 0;
	virtual void render(sf::RenderWindow& window, sf::View& view) = 0;
};

class MR : public Map {
public:
	MR();
	void loadMap() override;
	void loadPlatform() override;
	void render(sf::RenderWindow& window, sf::View& view) override;
};

class VE : public Map {
public:
	VE();
	void loadMap() override;
	void loadPlatform() override;
	void render(sf::RenderWindow& window, sf::View& view) override;
};