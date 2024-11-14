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

	float scaleFactor = 1.0f;  // 近景的缩放因子
	float maxScale = 2.0f;  // 最大缩放比例

public:
	void loadMap();
	void update(float positionX);
	void checkCollision(Character charactor);
	void render(sf::RenderWindow& window);
};

