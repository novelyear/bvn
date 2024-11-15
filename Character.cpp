#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"

Character::Character() {
	health = INIT_HEALTH;
	inAir = true;
	defending = false;
	stuned = false;
	jumpTimes = 0;
	attackStage = 0;
}


void Character::moveLeft() {
	left = true;
	defending = false;
	attackStage = 0;
	velocity.x = -MOVE_VELOCITY;
}
void Character::moveRight() {
	left = false;
	defending = false;
	attackStage = 0;
	velocity.x = MOVE_VELOCITY;
}
void Character::jump() {
	if(jumpTimes >= 2) {
		return;
	}
	jumpTimes++;
	velocity.y = JUMP_VELOCITY;
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
	if (inAir && velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}

	position.y += velocity.y;
	if (position.y >= CHARACTER_BOTTOM) {  
		position.y = CHARACTER_BOTTOM;  // ����λ��
		inAir = false;  // ����Ϊ���ڿ���
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
	if (!texture.loadFromFile("access\\gaara\\gaara1.png")) {
		std::cerr << "Failed to load player texture!" << std::endl;
	}
	else {
		sprite.setTexture(texture);
	}

}

void Character::render(sf::RenderWindow& window) {
	if (!sprite.getTexture()) {
		loadImage();
	}
	window.draw(sprite);
}