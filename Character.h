#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
enum class CharacterState {
	Default,
	Stand,
	Running,
	Jumping,
	Attacking,
	Hit,
	Kicked,
	Defending
};
enum class CharacterType {
	Gaara,
	Naruto,
	Itachi,
};
class Character
{
public:
	int health;
	std::vector<sf::Texture> runningTextures; //跑动
	std::vector<sf::Texture> jumpingTextures; // 跃起
	std::vector<sf::Texture> attackTextures; // 普攻
	std::vector<sf::Texture> standTextures; // 站立
	std::vector<sf::Texture> hitTextures; // 受击
	std::vector<sf::Texture> kickTextures; // 击飞

	CharacterState currentState;
	bool inAir; // 在空中
	bool left; // 朝向
	//bool defending; // 防御状态
	//bool stuned; // 被连招过程中的无法操作状态
	int jumpTimes; // 跳跃次数
	int attackStage; // 普攻阶段
	float elapsedTime; // 计时器
	int currentFrame;

	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::FloatRect rect;


	Character(); 
	virtual ~Character() = default; 

	void moveLeft(); 
	void moveRight();
	void jump();
	void down();

	void render(sf::RenderWindow& window);
	void updatePosition(sf::View view);
	void updateDirection(sf::Vector2f enemyPosition);
	void updateCollisionWithPlatform(std::vector<Platform> platforms);
	void updateCollisionWithEnemy(Character* enemy);
	void handleMove();
	void handleInput(sf::Event event);
	void gainVelocity(sf::Vector2f acceleration);

	virtual void useSkill() = 0;
	virtual void loadImage() = 0; // 加载图片
	virtual void takeDamage(int amount) = 0;
	virtual void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) = 0;
	virtual void updateSprite(float deltaTime) = 0;
};

