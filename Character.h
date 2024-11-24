#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
enum class CharacterState {
	Default, Stand, Running, Jumping, Fall, Hit, Kick, J1, J2, J3, U, KJ, KU, KI, I_before, I_after,
	I_miss, WI_before, WI_after, WI_miss, WU, WJ, S, SI_before, SI_after, SI_miss, SJ, SU, Flash
};
enum class CharacterType {
	Gaara,
	NarutoS,
};
class Character
{
public:
	int health;
	std::pair<int, int> animation; // ��������
	std::pair<int, int> animation_win; // ��������
		
	std::pair<int, int> run; //�ܶ�̬
	std::pair<int, int> jumping; // Ծ������̬
	std::pair<int, int> fall; // ��������̬
	std::pair<int, int> landed; // ��½̬
	std::pair<int, int> J1; // һ���չ�̬
	std::pair<int, int> J2; // �����չ�̬
	std::pair<int, int> J3; // �����չ�̬
	std::pair<int, int> stand; // վ��̬
	std::pair<int, int> hit; // �ܻ�̬
	std::pair<int, int> kick; // ����̬:�ݶ�
	std::pair<int, int> flashing; // ���̬
		
	std::pair<int, int> S; // ����̬������չ�����������Ž⿪����
	std::pair<int, int> KJ; // �����չ�
	std::pair<int, int> WJ; // �չ�2
	std::pair<int, int> SJ; // �չ�3
	std::pair<int, int> KU; // ����Զ��
	std::pair<int, int> SU; // Զ��3
	std::pair<int, int> WU; // Զ��2
	std::pair<int, int> U; // Զ��1
	std::pair<int, int> SI_before; // ����3�ͷ�
	std::pair<int, int> WI_before; // ����2�ͷ�
	std::pair<int, int> I_before; // ����1�ͷ�
		
	std::pair<int, int> SI_after; // ����3���к�
	std::pair<int, int> WI_after; // ����2���к�
	std::pair<int, int> I_after; // ����1���к�
		
	std::pair<int, int> SI_miss; // ����3δ����
	std::pair<int, int> WI_miss; // ����2δ����
	std::pair<int, int> I_miss; // ����1δ����

	std::vector<sf::Texture> textures;
	std::vector<sf::Vector2f> origins;
	


	CharacterState currentState;
	bool inAir; // �ڿ���
	bool left; // ����
	int jumpTimes; // ��Ծ����
	int attackStage; // �չ��׶�
	float elapsedTime; // ��ʱ��
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
	void flash();

	void render(sf::RenderWindow& window);
	void updatePosition(sf::View view);
	void updateDirection(sf::Vector2f enemyPosition);
	void updateCollisionWithPlatform(std::vector<Platform> platforms);
	void updateCollisionWithEnemy(Character* enemy);
	void handleMove();
	void handleInput(sf::Event event);
	void gainVelocity(sf::Vector2f acceleration);
	void loadResources(const std::string& directory, const std::string& rangeFile, const std::string& originFile);
	void updateSprite(float deltaTime);
	void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms);

	virtual void j1();
	virtual void j2();
	virtual void j3();
	virtual void kj();
	virtual void sj();
	virtual void su();
	virtual void s();


	virtual void takeDamage(int amount) = 0;
};

