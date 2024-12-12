#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"

bool Character::SameOr(bool a, bool b) {
	return !(a ^ b);
}

void Character::separate(Character* p1, Character* p2) {
	// 默认已经重合
	float r = std::fabs(p1->position.x - p2->position.x);
	bool left = p1->position.x < p2->position.x; // p1在左边就获得负的加速度
	float acceleration = REPULSION / r;
	p1->gainVelocity({ acceleration * left ? -1.f : 1.f, 0 });
	p2->gainVelocity({ acceleration * left ? 1.f : -1.f, 0 });
}

bool Character::hasEvents() const {
	return !eventQueue.empty();
}

EventType Character::popEvent() {
	EventType event = eventQueue.front();
	eventQueue.pop();
	return event;
}

Character::Character(): cUI(std::make_unique<CharacterUI>()) {
	attackStage = 0;
	currentState = CharacterState::Stand;
	health = INIT_HEALTH;
	chakra = 0;
	qi = 300;
	inAir = true;
	jumpTimes = 0;
	left = true;
	elapsedTime = PLAYER_FRAME;
	currentFrame = 0;
	onBoard = false;
	lastHit = CharacterState::Default;
}

void Character::moveLeft() {
	if (currentState == CharacterState::Running || currentState == CharacterState::Stand) {
		left = true;
	}
	attackStage = 0;
	velocity.x = -MOVE_VELOCITY;
	if (currentState == CharacterState::Stand || currentState == CharacterState::Landed) {
		currentFrame = 0;
		currentState = CharacterState::Running;
	}
}
void Character::moveRight() {
	if (currentState == CharacterState::Running || currentState == CharacterState::Stand) {
		left = false;
	}
	attackStage = 0;
	velocity.x = MOVE_VELOCITY;
	if (currentState == CharacterState::Stand || currentState == CharacterState::Landed) {
		currentFrame = 0;
		currentState = CharacterState::Running;
	}
}
void Character::jump() {
	if (jumpTimes >= 2) {
		return;
	}
	else if (jumpTimes >= 1 && velocity.y <= LIMIT_V) return;
	jumpTimes++;
	velocity.y = JUMP_VELOCITY;
	inAir = true;
	std::cout << "jumped" << std::endl;
	if (currentState != CharacterState::Jumping) {
		currentFrame = 0;
		currentState = CharacterState::Jumping;
	}
}

void Character::down() {
	if (currentState == CharacterState::Stand ||
        currentState == CharacterState::Running ||
        currentState == CharacterState::S) 
    {
		currentState = CharacterState::Jumping;
		currentFrame = 0;
		position.y += TOLERANCE + 0.01f;
	}
}

void Character::flash() {
	// 只有Onboard和空中一段跳时可以冲刺，消耗气，调用时已经判断气和跳跃
	if (currentState == CharacterState::Stand ||
		currentState == CharacterState::Jumping ||
		currentState == CharacterState::Fall ||
		currentState == CharacterState::Running) {
		velocity.x = left ? -FLASH_VELOCITY : FLASH_VELOCITY;
		currentState = CharacterState::Flash;
		currentFrame = 0;
		jumpTimes++;
		chakra -= CHAKRA_L;
	}
}

void Character::render(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Character::gainVelocity(sf::Vector2f acceleration) {
	this->velocity += acceleration;
}


