#pragma once
#include <SFML/Graphics.hpp>
enum class CharacterState {
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
	float elapsedTime; // ��ʱ��

	sf::Vector2f position;
	sf::Vector2f velocity;


	Character(); 
	virtual ~Character() = default; 

	void moveLeft(); 
	void moveRight();
	void jump();
	void render(sf::RenderWindow& window);
	void updatePosition();

	virtual void handleMove() = 0;
	virtual void handleInput(sf::Event event) = 0;
	virtual void useSkill() = 0;
	virtual void loadImage() = 0; // ����ͼƬ
	virtual void takeDamage(int amount) = 0;
	virtual void update(float deltaTime) = 0;
};

