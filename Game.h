#pragma once
#include "Map.h"
#include "Controller.h"
#include "CameraShake.h"
#include "Pause.h"
#include "GameAudio.h"

class StartUI;

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
	std::unique_ptr<StartUI> startUI;
	CameraShake cameraShake;
	Pause pause;
	GameAudio gameAudio;

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
	void loadAudios();

	void selectMap();
	void run();
	void processEvents();
	void update(float Time);
	void render();
	void gameover();
	void triggerShake(float intensity, float duration);
	void handleCharacterEvents(Character* character);
	void updateView(float deltaTime);

	std::vector<sf::Sprite> characterSprites;
	std::vector<CharacterType> characterTypes = { CharacterType::Gaara, CharacterType::NarutoS };
	int selectedCharacterIndex = 0;
	sf::Texture characterTextures[2]; // 用于加载选人头像的纹理
	sf::Texture blackPng;
	sf::Sprite blackBG;
};

class StartUI {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape startButton;
	sf::Texture buttonTextures[3]; // 常态、hover、press
	std::vector<sf::IntRect> anchors; // 动画帧的锚框
	int currentFrame = 0;
	sf::Clock frameClock; // 控制动画播放时间
	float frameDuration = 0.034f; // 每帧的持续时间
	bool mouseClicked = false; // 检测鼠标点击
	sf::RenderWindow& window;

	StartUI(sf::RenderWindow& win); 
	void loadResources(const std::string& textureFile, const std::string& anchorsFile,
		const std::string& buttonFile1, const std::string& buttonFile2, const std::string& buttonFile3);
	bool update(float deltaTime);
	void render();
};