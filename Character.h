#pragma once
#include <SFML/Graphics.hpp>
class Character
{
public:
	int health;
	sf::Texture texture;
	sf::Sprite sprite;
	bool inAir; // �ڿ���
	bool left; // ����
	bool defending; // ����״̬
	bool stuned; // �����й����е��޷�����״̬
	int jumpTimes; // ��Ծ����
	int attackStage; // �չ��׶�

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

