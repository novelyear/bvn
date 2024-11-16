#pragma once
#include <SFML/Graphics.hpp>
class Character
{
public:
	enum class CharacterState{
		Stand,
		Running,
		Jumping,
		Attacking,
		Hit,
		Kicked,
		Defending
	};
	int health;
	std::vector<sf::Texture> runningTextures; //跑动
	std::vector<sf::Texture> jumpingTextures; // 跃起
	std::vector<sf::Texture> attackTextures; // 普攻
	std::vector<sf::Texture> standTextures; // 站立
	std::vector<sf::Texture> hitTextures; // 受击
	std::vector<sf::Texture> kickTextures; // 击飞
	CharacterState currentState;
	sf::Sprite sprite;
	bool inAir; // 在空中
	bool left; // 朝向
	//bool defending; // 防御状态
	//bool stuned; // 被连招过程中的无法操作状态
	int jumpTimes; // 跳跃次数
	int attackStage; // 普攻阶段

	sf::Vector2f position;
	sf::Vector2f velocity;

	Character();

	void loadImage();
	void moveLeft();
	void moveRight();
	void jump();
	void takeDamage(int amount);
	void update();
	void render(sf::RenderWindow& window);
};

