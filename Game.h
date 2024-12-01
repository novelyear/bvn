#pragma once
#include "Map.h"
#include "Controller.h"
class Game
{
public:
	std::unique_ptr<Character> player;
	std::unique_ptr<Character> enemy;
	std::unique_ptr<Controller> enemyAI;
	std::unique_ptr<Map> map;


	static constexpr float minimumViewWidth = 320.0f; // 最小视图
	static constexpr float maximumViewWidth = 660.0f; // 最大视图

	sf::FloatRect getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition); // 
	sf::FloatRect testView(sf::Vector2f playerPosition);
	sf::View view;
	sf::RenderWindow window;
	Game(int width, int height, const std::string& title);


	void selectCharacter();
	void selectMap();
	void run();
	void processEvents();
	void update(float Time);
	void render();


	
};

