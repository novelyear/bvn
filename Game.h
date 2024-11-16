#pragma once
#include "Map.h"
#include "SoundManager.h"
class Game
{
	std::unique_ptr<Character> player;
	std::unique_ptr<Character> enemy;
	Map map;
	SoundManager soundManager;

	static constexpr float minimumViewWidth = 320.0f;
	static constexpr float maximumViewWidth = 800.0f;
	sf::FloatRect getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition);
public:
	sf::FloatRect testView(sf::Vector2f playerPosition);
	sf::View view;
	sf::RenderWindow window;
	Game(int width, int height, const std::string& title);
	void selectCharacter();
	void run();
	void processEvents();
	void update(float Time);
	void render();

	
};

