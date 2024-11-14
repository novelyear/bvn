#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "SoundManager.h"
class Game
{
	Player player;
	Enemy enemy;
	Map map;
	SoundManager soundManager;
public:
	sf::View view;
	sf::RenderWindow window;
	Game(int width, int height, const std::string& title);
	void run();
	void processEvents();
	void update();
	void render();
	float getCenter();
};

