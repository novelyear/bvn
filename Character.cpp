#include "Character.h"
#include <bits/stdc++.h>
void Character::moveLeft() {
	left = true;
	defending = false;
	attackStage = 0;
	velocity.x = -1.0f;
}
void Character::moveRight() {
	left = false;
	defending = false;
	attackStage = 0;
	velocity.x = 1.0f;
}
void Character::jump() {
	if(jumpTimes >= 2) {
		return;
	}
	jumpTimes++;
	velocity.y = -2.f;
	inAir = true;
}


void Character::takeDamage(int amount) {}

void Character::update() {



	position.x += velocity.x;
	velocity.x = 0;
	if (inAir) {
		velocity.y += 0.01f;
	}

	position.y += velocity.y;
	if (position.y >= 400.f) {  // �������߶�Ϊ 400
		position.y = 400.f;  // ����λ��
		inAir = false;  // ����Ϊ���ڿ���
		velocity.y = 0.f;  // �����ֱ�ٶ�
		jumpTimes = 0;  // ������Ծ����
	}

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