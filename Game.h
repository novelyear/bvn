#pragma once
#include "Map.h"
#include "Controller.h"
class Game
{
	float currentViewLeft = 0.f;
	float currentViewTop = 0.f;
	float currentViewWidth = minimumViewWidth;
	float currentViewHeight = minimumViewWidth * 0.75f;
public:
	std::unique_ptr<Character> player;
	std::unique_ptr<Character> enemy;
	std::unique_ptr<Controller> enemyAI;
	std::unique_ptr<Map> map;

	GameState state; // 游戏状态

	static constexpr float minimumViewWidth = 320.0f; // 最小视图
	static constexpr float maximumViewWidth = 660.0f; // 最大视图

	sf::FloatRect getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition, float deltaTime); // 
	sf::FloatRect testView(sf::Vector2f playerPosition);
	sf::View view;
	sf::RenderWindow window;
	Game(int width, int height, const std::string& title);


	void selectCharacter();
	void handleCharacterSelection();

	void selectMap();
	void run();
	void processEvents();
	void update(float Time);
	void render();

	std::vector<sf::Sprite> characterSprites;
	std::vector<CharacterType> characterTypes = { CharacterType::Gaara, CharacterType::NarutoS };
	int selectedCharacterIndex = 0;
	sf::Texture characterTextures[2]; // 用于加载选人头像的纹理
	
};

