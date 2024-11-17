#pragma once
#include <SFML/Graphics.hpp>
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


	Character(); 
	virtual ~Character() = default; 

	void moveLeft(); 
	void moveRight();
	void jump();
	void render(sf::RenderWindow& window);
	void updatePosition();
	void handleMove();
	void handleInput(sf::Event event);

	virtual void useSkill() = 0;
	virtual void loadImage() = 0; // 加载图片
	virtual void takeDamage(int amount) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void updateSprite(float deltaTime) = 0;
};

