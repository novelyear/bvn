#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"

Character::Character() {
	health = INIT_HEALTH;
	currentState = CharacterState::Stand;
	jumpTimes = 0;
	attackStage = 0;
}


void Character::moveLeft() {
	left = true;
	attackStage = 0;
	velocity.x = -MOVE_VELOCITY;
}
void Character::moveRight() {
	left = false;
	attackStage = 0;
	velocity.x = MOVE_VELOCITY;
}
void Character::jump() {
	if(jumpTimes >= 2) {
		return;
	}
	jumpTimes++;
	velocity.y = JUMP_VELOCITY;
	currentState = CharacterState::Jumping;
	inAir = true;
}

void Character::takeDamage(int amount) {}

void Character::update() {
	position.x += velocity.x;

	if (position.x <= LEFT_BORDER) {
		position.x = LEFT_BORDER;
	}
	else if (position.x >= RIGHT_BORDER) {
		position.x = RIGHT_BORDER;
	}

	//velocity.x = 0;
	if (currentState == CharacterState::Jumping && velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}

	position.y += velocity.y;
	if (position.y >= CHARACTER_BOTTOM) {  
		position.y = CHARACTER_BOTTOM;  // ����λ��
		inAir = false;
		currentState = CharacterState::Stand;  // ����������
		velocity.y = 0.f;  // �����ֱ�ٶ�
		jumpTimes = 0;  // ������Ծ����
	}
	sf::FloatRect bounds = sprite.getLocalBounds();
	float width = bounds.width;
	float height = bounds.height;
	// ����ԭ�㵽�ײ�����
	sprite.setOrigin(width / 2.f, height);  // �ײ�������ˮƽ���� + ��ֱ�ײ�

	sprite.setPosition(position);
}

void Character::loadImage() {
	for (int i = 1; i <= 4; ++i) {
		// �����ļ���
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			standTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 11; i <= 16; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			runningTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 18; i <= 21; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			jumpingTextures.push_back(texture); 
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 23; i <= 24; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			hitTextures.push_back(texture); 
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 25; i <= 28; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			kickTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
}

void Character::render(sf::RenderWindow& window) {
	if (!sprite.getTexture()) {
		loadImage();
	}
	window.draw(sprite);
}