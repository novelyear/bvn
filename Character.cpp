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
	if (position.y >= 400.f) {  // 假设地面高度为 400
		position.y = 400.f;  // 重置位置
		inAir = false;  // 设置为不在空中
		velocity.y = 0.f;  // 清除竖直速度
		jumpTimes = 0;  // 重置跳跃次数
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