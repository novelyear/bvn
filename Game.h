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

	static constexpr float minimumViewWidth = 1000.0f;
	static constexpr float maximumViewWidth = 1000.0f;
	sf::FloatRect getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition);
public:
	sf::View view;
	sf::RenderWindow window;
	Game(int width, int height, const std::string& title);
	void run();
	void processEvents();
	void update();
	void render();
	
};

