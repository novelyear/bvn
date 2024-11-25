#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"



void Character::updatePosition(sf::View view) {
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	// 获取视图的当前边界
	float left = center.x - size.x / 2.f;
	float right = center.x + size.x / 2.f;


	position.x += velocity.x;
	if (currentState == CharacterState::Running ||
		currentState == CharacterState::Jumping ||
		currentState == CharacterState::Fall ||
		currentState == CharacterState::Stand)
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
		currentState == CharacterState::Flash)
		&& velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}

	position.y += velocity.y;
	// 兜底机制
	if (position.y >= CHARACTER_BOTTOM) {
		position.y = CHARACTER_BOTTOM;  // 重置位置
		inAir = false;
		//if (currentState != CharacterState::Running) {
		//	currentState = CharacterState::Stand;  // run和stand都需要platform
		//}
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
	if (platforms.empty() || velocity.y < 0) return;
	bool onBoard = false;
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
			if (currentState == CharacterState::Jumping || // 注意与上面的兜底机制保持一致
				currentState == CharacterState::Fall) {
				currentState = CharacterState::Stand;
			}
			velocity.y = 0.f;  // 清除竖直速度
			jumpTimes = 0;  // 重置跳跃次数

			break;
		}
	}
	if (!onBoard && (currentState == CharacterState::Stand || currentState == CharacterState::Running)) {
		currentState = CharacterState::Jumping;
		currentFrame = 0;
	}
}

void separate(Character* p1, Character* p2) {
	// 默认已经重合
	float r = std::fabs(p1->position.x - p2->position.x);
	bool left = p1->position.x < p2->position.x; // p1在左边就获得负的加速度
	float acceleration = REPULSION / r;
	p1->gainVelocity({ acceleration * left ? -0.2f : 0.2f, 0 });
	p2->gainVelocity({ acceleration * left ? 0.2f : -0.2f, 0 });
}

void Character::updateCollisionWithEnemy(Character* enemy) {
	if (currentState == CharacterState::Flash || enemy->currentState == CharacterState::Flash) {
		return;
	}
	// 素材尺寸不一，如果设为属性避免重复计算，那在更新精灵时需要加判断，目前帧率溢出，可不优化
	sf::FloatRect playerRect = this->sprite.getLocalBounds();
	sf::FloatRect enemyRect = enemy->sprite.getLocalBounds();
	playerRect.left = this->position.x - playerRect.width / 2.f;
	playerRect.top = this->position.y - playerRect.height / 2.f;
	enemyRect.left = enemy->position.x - enemyRect.width / 2.f;
	enemyRect.top = enemy->position.y - enemyRect.height / 2.f;
	// 前提：不可能完全重合==>重合点归入一边即可
	// 似乎原游戏存在重量，人物相推速度变化不一致，有的减半，有的更慢
	// 这里都设置为一样的重量，如果有人物挡道，则速度减半
	if (!playerRect.intersects(enemyRect)) return;
	if (std::fabs(this->position.y - enemy->position.y) < TOLERANCE && this->velocity.x != 0.f) { // 同高度，水平碰撞
		this->velocity.x /= 4.f;
		enemy->gainVelocity({ this->velocity.x, 0.f });
	}
	separate(this, enemy);
}

