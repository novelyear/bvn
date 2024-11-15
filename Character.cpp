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
		position.y = CHARACTER_BOTTOM;  // 重置位置
		inAir = false;  // 设置为不在空中
		velocity.y = 0.f;  // 清除竖直速度
		jumpTimes = 0;  // 重置跳跃次数
	}
	sf::FloatRect bounds = sprite.getLocalBounds();
	float width = bounds.width;
	float height = bounds.height;
	// 设置原点到底部中心
	sprite.setOrigin(width / 2.f, height);  // 底部中心是水平中心 + 垂直底部

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