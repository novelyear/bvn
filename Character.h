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
	std::vector<sf::Texture> runningTextures; //�ܶ�
	std::vector<sf::Texture> jumpingTextures; // Ծ��
	std::vector<sf::Texture> attackTextures; // �չ�
	std::vector<sf::Texture> standTextures; // վ��
	std::vector<sf::Texture> hitTextures; // �ܻ�
	std::vector<sf::Texture> kickTextures; // ����
	CharacterState currentState;
	sf::Sprite sprite;
	bool inAir; // �ڿ���
	bool left; // ����
	//bool defending; // ����״̬
	//bool stuned; // �����й����е��޷�����״̬
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

