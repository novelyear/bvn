#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"
#include "Map.h"

void Character::updatePosition(sf::View view) {
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	// 获取视图的当前边界
	float left = center.x - size.x / 2.f;
	float right = center.x + size.x / 2.f;


	position.x += velocity.x;

	if (currentState != CharacterState::Flash && 
		currentState != CharacterState::Hit &&
		currentState != CharacterState::KU &&
		currentState != CharacterState::U &&
		currentState != CharacterState::I_before &&
		(currentState != CharacterState::Kick || currentFrame > 7)) // 7就是落地帧，两个人物都差不多
	{
		velocity.x = 0;
	}
	if (position.x <= left) {
		position.x = left;
	}
	else if (position.x >= right) {
		position.x = right;
	}

	if ((currentState == CharacterState::Jumping ||
		currentState == CharacterState::Fall ||
		currentState == CharacterState::Flash || 
		currentState == CharacterState::Hit ||
		currentState == CharacterState::Kick)
		&& velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}
	// 转下落
	if (currentState == CharacterState::Jumping && velocity.y > 0) {
		currentState = CharacterState::Fall;
		currentFrame = 0;
	}

	position.y += velocity.y;
	// 兜底机制
	if (position.y >= CHARACTER_BOTTOM) {
		position.y = CHARACTER_BOTTOM;  // 重置位置
		inAir = false;
		onBoard = true;
		if (currentState == CharacterState::KU) {
			currentState = CharacterState::KU_down;  // run和stand都需要platform
			currentFrame = 0;
		}
		velocity.y = 0.f;  // 清除竖直速度
		jumpTimes = 0;  // 重置跳跃次数
	}
}

bool XOR(bool a, bool b) {
	return (a + b) % 2;
}


void Character::updateDirection(sf::Vector2f enemyPosition) {
	if (currentState != CharacterState::Stand) return;
	// 站立时，自动转向敌人所在方向
	if (XOR(left, enemyPosition.x < this->position.x)) {
		left = !left;
	}
}

void Character::updateCollisionWithPlatform(std::vector<Platform> platforms) {
	if (platforms.empty() || velocity.y < 0 ||
		this->currentState == CharacterState::KU || this->currentState == CharacterState::KU_down) return;
	onBoard = false;
	// 遍历所有platform，判断是否在上面
	for (const auto& platform : platforms) {
		sf::Vector2f platformStart = platform.startPosition;
		float platformWidth = platform.width;

		// 检测是否站在平台上
		if (position.y >= platformStart.y &&  // 位于平台高度
			position.y <= platformStart.y + TOLERANCE && // 允许小范围误差
			position.x >= platformStart.x && // 在平台范围内
			position.x <= platformStart.x + platformWidth) {
			onBoard = true;

			position.y = platformStart.y;  // 站在上面
			inAir = false;
			if (currentState == CharacterState::Jumping ||
				currentState == CharacterState::Fall) {
				currentState = CharacterState::Landed;
				currentFrame = 0;
			}
			velocity.y = 0.f;  // 清除竖直速度
			jumpTimes = 0;  // 重置跳跃次数

			break;
		}
	}
	if (!onBoard && (currentState == CharacterState::Stand || currentState == CharacterState::Running)) {
		currentState = CharacterState::Fall;
		currentFrame = 0;
	}
}


// 传入敌人的特效池，从中遍历，判断是否与特效碰撞。
// 自己受击 & 修改敌方大招命中状态
void Character::updateCollisionWithEffect(Character * enemy) {
	if (currentState == CharacterState::Flash || currentState == CharacterState::Kick) {
		return;
	}

	sf::FloatRect playerRect;
	playerRect.width = 40.f;playerRect.height = 50.f; // 自己的本体宽40高50，原点为中心
	if (this->left) {
		playerRect.left = this->position.x + sprite.getOrigin().x - playerRect.width;
	}
	else playerRect.left = this->position.x - playerRect.width;
	playerRect.top = this->position.y - playerRect.height;
	for (auto& e : enemy->effects->effects) {
		if (e->currentState == EffectState::Default) continue;

		sf::FloatRect eRect = e->sprite.getLocalBounds();
		eRect.left = e->left ? e->position.x - (eRect.width - e->sprite.getOrigin().x) : e->position.x - e->sprite.getOrigin().x;
		eRect.top = e->position.y - e->sprite.getOrigin().y;
		if (!playerRect.intersects(eRect)) continue;
		// 有碰撞，修改特效发出者的命中状态，修改特效的命中状态
		switch (e->currentState) {
			case EffectState::I_before:
				if (e->currentFrame < 13) break;
				e->currentState = EffectState::I_after;
				e->currentFrame = 0;
				enemy->currentState = CharacterState::I_after;
				enemy->currentFrame = 0;
				break;
			case EffectState::WI_before:
				e->currentState = EffectState::Default;
				e->currentFrame = 0;
				enemy->currentState = CharacterState::WI_after;
				enemy->currentFrame = 0;
				break;
			case EffectState::SI_before:
				if (e->currentFrame < 13) break;
				e->currentState = EffectState::Default;
				e->currentFrame = 0;
				enemy->currentState = CharacterState::SI_after;
				enemy->currentFrame = 0;
				break;
			case EffectState::KI_before:
				e->currentState = EffectState::KI_after;
				e->currentFrame = 0;
				break;
			default:
				break;
		}

		if (hitTimer.getElapsedTime().asSeconds() < HIT_INTERVAL) { // 每 HIT_INTERVAL 秒受击判断一次
			return;
		}
		hitTimer.restart(); // 重设计时器

		// 根据特效攻击类型获取效果
		enemy->exertEffect(this, e.get());
		this->real ? printf("I'm hited\n") : printf("he is hitted\n");
	}
}
