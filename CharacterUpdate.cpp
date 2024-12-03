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
		(currentState != CharacterState::Kick || currentFrame < 7)) // 7就是落地帧
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
	return (a + b) != 1;
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
				currentState = CharacterState::Stand;
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
	playerRect.width = 40.f;playerRect.height = 50.f; // 自己的本体宽40高50，原点为中心
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
			this->velocity.x /= 4.f; // 速度除以4，减速推动
			enemy->gainVelocity({ this->velocity.x, 0.f });
		}
		separate(this, enemy);
		return;
	}
	// 敌人正在攻击, 且处于攻击帧(宽度大于40，包含特效)，所以排除敌人的本体
	if (!enemy->canTouch()) {
		if (!enemy->left) {
			enemyRect.left += 40.f;
		}
		enemyRect.width -= 40.f;
	}

	if (enemyRect.width <= 0.f || !playerRect.intersects(enemyRect)) return; // 如果没被K
	if (hitTimer.getElapsedTime().asSeconds() < HIT_INTERVAL) { // 每0.2秒受击判断一次
		return;
	}
	hitTimer.restart(); // 重设计时器
    // 翻译：敌人的特效与自己的本体有碰撞 & 敌人面向本体 & 敌人正在攻击 = 被打到了
	bool beAttacked = SameOr(enemy->left, this->position.x < enemy->position.x) && !enemy->canTouch();
	if (beAttacked) {
		if (currentState == CharacterState::S) {
			chakra -= 10;
			return;
		}
		this->real ? printf("I'm hited\n") : printf("he is hitted\n");
		enemy->exertEffect(this, (int)enemy->currentState);
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
	else playerRect.left = this->position.x - sprite.getOrigin().x;
	playerRect.top = this->position.y - this->sprite.getOrigin().y;

	for (auto& e : enemy->effects->effects) {
		if (e->currentState == EffectState::Default) continue;

		sf::FloatRect eRect = e->sprite.getLocalBounds();
		eRect.left = e->position.x - e->sprite.getOrigin().x;
		eRect.top = e->position.y - e->sprite.getOrigin().y;
		if (!playerRect.intersects(eRect)) continue;
		// 有碰撞，修改敌人的命中状态，修改特效的命中状态
		switch (enemy->currentState) {
			case CharacterState::I_before:
				e->currentState = EffectState::I_after;
				e->currentFrame = 0;
				enemy->currentState = CharacterState::I_after;
				enemy->currentFrame = 0;
				break;
			case CharacterState::WI_before:
				e->currentState = EffectState::WI_after;
				e->currentFrame = 0;
				enemy->currentState = CharacterState::WI_after;
				enemy->currentFrame = 0;
				break;
			case CharacterState::SI_before:
				e->currentState = EffectState::SI_after;
				e->currentFrame = 0;
				enemy->currentState = CharacterState::SI_after;
				enemy->currentFrame = 0;
				break;
			default:
				break;
		}
		// 根据特效攻击类型获取效果
		enemy->exertEffect(this, (int)enemy->currentState);
		this->real ? printf("I'm hited\n") : printf("he is hitted\n");
	}
}
