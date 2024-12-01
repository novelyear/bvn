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
	//if (currentState == CharacterState::Running ||
	//	currentState == CharacterState::Jumping ||
	//	currentState == CharacterState::Fall ||
	//	currentState == CharacterState::Stand ||
	//	currentState == CharacterState::S ||
	//	currentState == CharacterState::S_Release)
	if (currentState != CharacterState::Flash)
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

bool SameOr(bool a, bool b) {
	return (a + b) != true;
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
		currentState = CharacterState::Fall;
		currentFrame = 0;
	}
}

void separate(Character* p1, Character* p2) {
	// 默认已经重合
	float r = std::fabs(p1->position.x - p2->position.x);
	bool left = p1->position.x < p2->position.x; // p1在左边就获得负的加速度
	float acceleration = REPULSION / r;
	p1->gainVelocity({ acceleration * left ? -1.f : 1.f, 0 });
	p2->gainVelocity({ acceleration * left ? 1.f : -1.f, 0 });
}
// 检测自己是否碰到敌人
void Character::updateCollisionWithEnemy(Character* enemy) {
	// 敌方冲刺状态和击飞状态不检测；
	// 己方冲刺状态无敌，不检测
	if (currentState == CharacterState::Flash || currentState == CharacterState::Kick ||
		enemy->currentState == CharacterState::Flash || enemy->currentState == CharacterState::Kick) {
		return;
	}
	// 自己的Rect应该只包括自己的身体，不能包括特效，比如KU的特效被打到，不能被认定为被打到。
	sf::FloatRect playerRect;
	playerRect.width = 40.f;playerRect.height = 50.f;
	sf::FloatRect enemyRect = enemy->sprite.getLocalBounds();
	if (this->left) {
		playerRect.left = this->position.x + sprite.getOrigin().x - playerRect.width;
	}
	else playerRect.left = this->position.x - sprite.getOrigin().x;
	if (enemy->left)
		enemyRect.left = enemy->position.x + enemy->sprite.getOrigin().x - enemyRect.width;
	else
		enemyRect.left = enemy->position.x - enemy->sprite.getOrigin().x;
	playerRect.top = this->position.y - this->sprite.getOrigin().y;
	enemyRect.top = enemy->position.y - enemy->sprite.getOrigin().y;
	// 双方都没有攻击，全判定
	if (enemy->canTouch() && this->canTouch()) {
		if (!playerRect.intersects(enemyRect)) return; // 如果根本没有重合，取消后续操作
		// 非攻击状态碰撞：
		if (std::fabs(this->position.y - enemy->position.y) < TOLERANCE) { // 同高度，水平碰撞
			this->velocity.x /= 4.f;
			enemy->gainVelocity({ this->velocity.x, 0.f });
		}
		separate(this, enemy);
		return;
	}
	// 敌人正在攻击，由于是检测自己是否被K，所以排除敌人的本体
	if (!enemy->canTouch()) {
		if (!enemy->left) {
			enemyRect.left += 30.f;
		}
		enemyRect.width -= 30.f;
	}

	if (!playerRect.intersects(enemyRect)) return; // 如果没被K
    // 被敌方的特效K到了
	bool beAttacked = SameOr(enemy->left, this->position.x < enemy->position.x) && !enemy->canTouch();
	if (beAttacked) {
		this->real ? printf("I'm hited\n") : printf("he is hitted\n");
	}
}

void Character::updateCollisionWithEffect(std::unique_ptr<EffectPool> effects) {

}

