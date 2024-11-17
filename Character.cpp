#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"


Character::Character(){
	attackStage = 0;
	currentState = CharacterState::Stand;
	health = INIT_HEALTH;
	inAir = true;
	jumpTimes = 0;
	left = true;
	elapsedTime = PLAYER_FRAME;
	currentFrame = 0;
}

void Character::moveLeft() {
	left = true;
	attackStage = 0;
	velocity.x = -MOVE_VELOCITY;
	if (currentState == CharacterState::Stand) {
		currentFrame = 0;
		currentState = CharacterState::Running;
	}
}
void Character::moveRight() {
	left = false;
	attackStage = 0;
	velocity.x = MOVE_VELOCITY;
	if (currentState == CharacterState::Stand) {
		currentFrame = 0;
		currentState = CharacterState::Running;
	}
}
void Character::jump() {
	if(jumpTimes >= 2) {
		return;
	}
	jumpTimes++;
	velocity.y = JUMP_VELOCITY;
	inAir = true;
	if (currentState != CharacterState::Jumping) {
		currentFrame = 0;
		currentState = CharacterState::Jumping;
	}
}


void Character::render(sf::RenderWindow& window) {
	sf::Sprite test;
	test.setTexture(standTextures[0]);
	test.setPosition({ LEFT_BORDER + 100.f, GROUND });
	window.draw(test);
	window.draw(sprite);
}

void Character::updatePosition() {
	position.x += velocity.x;
	if (position.x <= LEFT_BORDER) {
		position.x = LEFT_BORDER;
	}
	else if (position.x >= RIGHT_BORDER) {
		position.x = RIGHT_BORDER;
	}

	if (currentState == CharacterState::Jumping && velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}

	position.y += velocity.y;

	if (position.y >= CHARACTER_BOTTOM) {
		position.y = CHARACTER_BOTTOM;  // 重置位置
		inAir = false;
		if (currentState != CharacterState::Running) {

			currentState = CharacterState::Stand;  // run和stand都需要platform
		}
		velocity.y = 0.f;  // 清除竖直速度
		jumpTimes = 0;  // 重置跳跃次数
	}
}

void Character::handleMove() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveRight();
		return;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = 0;  // 停止水平移动
		if (currentState == CharacterState::Running) {
			currentState = CharacterState::Stand;
			currentFrame = 0;
		}
		return;
	}
}

void Character::handleInput(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::K)
			jump();
	}
}

