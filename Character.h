#pragma once
#include <SFML/Graphics.hpp>
class Character
{
public:
	int health;
	sf::Texture texture;
	sf::Sprite sprite;
	bool inAir; // 在空中
	bool left; // 朝向
	bool defending; // 防御状态
	bool stuned; // 被连招过程中的无法操作状态
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

