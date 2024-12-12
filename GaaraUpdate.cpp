#include "Gaara.h"
#include "Constants.h"
#include "Map.h"

void Gaara::update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) {
	updateSprite(deltaTime, enemy->position);
	// 敌人与攻击特效的碰撞
	updateCollisionWithEffect(enemy);
	updateCollisionWithPlatform(platforms);
	updateCollisionWithEnemy(enemy);
	updatePosition(view);
	updateDirection(enemy->position);
	effects->update(deltaTime, view);
	cUI->update(this, view);
	// chakra更新，暂时写在这里
	if (currentState != CharacterState::Flash && currentState != CharacterState::S) {
		chakra++;
		if (chakra >= MAX_CHAKRA) {
			chakra = MAX_CHAKRA;
		}
	}
}

// 只有两个人物，放弃通用性，针对NarutoS写碰撞检测
void Gaara::updateCollisionWithEnemy(Character* enemy) {
	// 敌方冲刺状态和击飞状态不检测；
	// 己方冲刺状态无敌，不检测
	if (currentState == CharacterState::Flash || currentState == CharacterState::Kick ||
		enemy->currentState == CharacterState::Flash || enemy->currentState == CharacterState::Kick) {
		return;
	}
	// 自己的Rect应该只包括自己的身体，不能包括特效，比如特效被打到，不能被认定为被打到。
	sf::FloatRect playerRect;
	playerRect.width = 40.f;playerRect.height = 50.f; // 自己的本体宽40高50，原点为中心
	if (this->left) {
		playerRect.left = this->position.x + sprite.getOrigin().x - playerRect.width;
	}
	else playerRect.left = this->position.x - sprite.getOrigin().x;
	sf::FloatRect enemyRect = enemy->sprite.getLocalBounds();
	if (enemy->left)
		enemyRect.left = enemy->position.x + enemy->sprite.getOrigin().x - enemyRect.width;
	else
		enemyRect.left = enemy->position.x - enemy->sprite.getOrigin().x;
	playerRect.top = this->position.y - playerRect.height;
	enemyRect.top = enemy->position.y - enemy->sprite.getOrigin().y;
	// 双方都没有攻击
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
	// 对于NarutoS，KJ SUU WJ KU取除体右段，WU WUU取右上角，其他全匹配
	if (enemy->currentState == CharacterState::KJ ||
		enemy->currentState == CharacterState::SUU || 
		enemy->currentState == CharacterState::WJ || 
		enemy->currentState == CharacterState::KU) { // 左裁40
		if (!enemy->left) {
			enemyRect.left += 40.f;
		}
		enemyRect.width -= 40.f;
	}
	else if (enemy->currentState == CharacterState::WU ||
			 enemy->currentState == CharacterState::WUU) {// 左裁35，下裁40
		enemyRect.height -= 40.f;
		if (!enemy->left) {
			enemyRect.left += 35.f;
		}
		enemyRect.width -= 35.f;
	}

	if (enemyRect.width <= 0.f || !playerRect.intersects(enemyRect)) return; // 如果没被K
	switch (enemy->currentState) {
	case CharacterState::U:
		enemy->currentState = CharacterState::U_after;
		enemy->currentFrame = 0;
		break;
	case CharacterState::I_before:
		enemy->velocity.x = 0;
		break;
	}
	if (hitTimer.getElapsedTime().asSeconds() < HIT_INTERVAL) { // 每 HIT_INTERVAL 秒受击判断一次
		return;
	}
	hitTimer.restart(); // 重设计时器
	// 翻译：敌人的特效与自己的本体有碰撞 & 敌人面向本体 & 敌人正在攻击 = 被打到了
	if (!enemy->canTouch()) {
		if (currentState == CharacterState::S) {
			chakra -= 10;
			return;
		}
		this->real ? printf("I'm hited\n") : printf("he is hitted\n");
		enemy->exertEffect(this);
	}
}


void Gaara::updateSprite(float deltaTime, sf::Vector2f enemyPosition) {
	if (origins.empty()) return;
	elapsedTime += deltaTime;
	if (elapsedTime > PLAYER_FRAME) {
		switch (currentState) {
		case CharacterState::Default:
			sprite.setTextureRect(anchors[0]);
			sprite.setOrigin(origins[0]);
			break;
		case CharacterState::Stand:
			sprite.setTextureRect(anchors[stand.first + currentFrame]);
			sprite.setOrigin(origins[stand.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (stand.second - stand.first);
			break;
		case CharacterState::Running:
			sprite.setTextureRect(anchors[run.first + currentFrame]);
			sprite.setOrigin(origins[run.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (run.second - run.first);
			break;
		case CharacterState::Jumping:
			sprite.setTextureRect(anchors[jumping.first + currentFrame]);
			sprite.setOrigin(origins[jumping.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (jumping.second - jumping.first);
			break;
		case CharacterState::Landed:
			sprite.setTextureRect(anchors[landed.first + currentFrame]);
			sprite.setOrigin(origins[landed.first + currentFrame]);
			currentFrame++;
			if (currentFrame + landed.first > landed.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::Flash:
			sprite.setTextureRect(anchors[flashing.first + currentFrame]);
			sprite.setOrigin(origins[flashing.first + currentFrame]);
			currentFrame++;
			if (currentFrame + flashing.first > flashing.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::Fall:
			sprite.setTextureRect(anchors[fall.first + currentFrame]);
			sprite.setOrigin(origins[fall.first + currentFrame]);
			if (currentFrame + fall.first < fall.second) currentFrame++;
			break;
		case CharacterState::J1:
			sprite.setTextureRect(anchors[J1.first + currentFrame]);
			sprite.setOrigin(origins[J1.first + currentFrame]);
			currentFrame++;
			if (currentFrame + J1.first > J1.second) {
				if (attackStage > 1) {
					currentState = CharacterState::J2;
					currentFrame = 0;
				}
				else {
					currentState = CharacterState::Stand;
					currentFrame = 0;
					attackStage = 0;
				}
			}
			break;
		case CharacterState::J2:
			sprite.setTextureRect(anchors[J2.first + currentFrame]);
			sprite.setOrigin(origins[J2.first + currentFrame]);
			currentFrame++;
			if (currentFrame + J2.first > J2.second) {
				if (attackStage > 2) {
					currentState = CharacterState::J3;
					currentFrame = 0;
				}
				else {
					currentState = CharacterState::Stand;
					currentFrame = 0;
					attackStage = 0;
				}
			}
			break;
		case CharacterState::J3:
			sprite.setTextureRect(anchors[J3.first + currentFrame]);
			sprite.setOrigin(origins[J3.first + currentFrame]);
			if (currentFrame == 0) audioEventQueue.push("gaara_attack");
			currentFrame++;
			if (currentFrame + J3.first > J3.second) {
				attackStage = 0;
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KJ:
			sprite.setTextureRect(anchors[KJ.first + currentFrame]);
			sprite.setOrigin(origins[KJ.first + currentFrame]);
			currentFrame++;
			if (currentFrame + KJ.first > KJ.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::SJ:
			sprite.setTextureRect(anchors[SJ.first + currentFrame]);
			sprite.setOrigin(origins[SJ.first + currentFrame]);
			currentFrame++;
			if (currentFrame + SJ.first > SJ.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::SU:
			sprite.setTextureRect(anchors[SU.first + currentFrame]);
			sprite.setOrigin(origins[SU.first + currentFrame]);
			currentFrame++;
			if (currentFrame + SU.first > SU.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::S:
			sprite.setTextureRect(anchors[S.first + currentFrame]);
			sprite.setOrigin(origins[S.first + currentFrame]);
			if (currentFrame + S.first < S.second) {
				currentFrame++;
			}
			break;
		case CharacterState::S_Release:
			sprite.setTextureRect(anchors[S.second - currentFrame]);
			sprite.setOrigin(origins[S.second - currentFrame]);
			currentFrame++;
			if (S.second - currentFrame < S.first) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::WJ:
			sprite.setTextureRect(anchors[WJ.first + currentFrame]);
			sprite.setOrigin(origins[WJ.first + currentFrame]);
			currentFrame++;
			if (currentFrame + WJ.first > WJ.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::WU:
			sprite.setTextureRect(anchors[WU.first + currentFrame]);
			sprite.setOrigin(origins[WU.first + currentFrame]);
			currentFrame++;
			if (currentFrame == 4) { // 第4帧后，特效离体
				sf::Vector2f offset = { left ? -36.f : 36.f, -58.f }; // 水平偏移量左右对称
				effects->run(enemyPosition, EffectState::WU, left);// 位置偏移量硬编码36，58
			}
			if (currentFrame + WU.first > WU.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::WI_before:
			sprite.setTextureRect(anchors[WI_before.first + currentFrame]);
			sprite.setOrigin(origins[WI_before.first + currentFrame]);
			if (currentFrame == 0) audioEventQueue.push("gaara_WI");
			currentFrame++;
			if (currentFrame + WI_before.first > WI_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::WI_after:
			sprite.setTextureRect(anchors[WI_after.first + currentFrame]);
			sprite.setOrigin(origins[WI_after.first + currentFrame]);
			currentFrame++;
			if (currentFrame + WI_after.first > WI_after.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::SI_before:
			sprite.setTextureRect(anchors[SI_before.first + currentFrame]);
			sprite.setOrigin(origins[SI_before.first + currentFrame]);
			if (currentFrame == 0) audioEventQueue.push("gaara_SI");
			currentFrame++;
			if (currentFrame == 5) { // 5帧后触发特效
				effects->run(enemyPosition, EffectState::SI_before, left);
			}
			if (currentFrame + SI_before.first > SI_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::SI_after:
			sprite.setTextureRect(anchors[SI_after.first + currentFrame]);
			sprite.setOrigin(origins[SI_after.first + currentFrame]);
			currentFrame++;
			if (currentFrame == 5) { // 5帧后触发特效
				effects->run(enemyPosition, EffectState::SI_after, left);
			}
			if (currentFrame + SI_after.first > SI_after.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::I_before:
			sprite.setTextureRect(anchors[I_before.first + currentFrame]);
			sprite.setOrigin(origins[I_before.first + currentFrame]);
			if (currentFrame == 0) audioEventQueue.push("gaara_I");
			currentFrame++;
			if (currentFrame == 1) { // 1帧后触发特效
				effects->run(enemyPosition, EffectState::I_before, left);
			}
			if (currentFrame + I_before.first > I_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::I_after:
			sprite.setTextureRect(anchors[I_after.first + currentFrame]);
			sprite.setOrigin(origins[I_after.first + currentFrame]);
			currentFrame++;
			if (currentFrame + I_after.first > I_after.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::U:
			sprite.setTextureRect(anchors[U.first + currentFrame]);
			sprite.setOrigin(origins[U.first + currentFrame]);
			currentFrame++;
			if (currentFrame == 11) { // 第11帧后，特效离体
				sf::Vector2f offset = { left ? -36.f : 36.f, -58.f }; // 水平偏移量左右对称
				effects->run(position + offset, EffectState::U, left);// 位置偏移量硬编码36，58
			}
			if (U.second - currentFrame < U.first) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KU:
			sprite.setTextureRect(anchors[KU.first + currentFrame]);
			sprite.setOrigin(origins[KU.first + currentFrame]);
			currentFrame++;
			if (currentFrame + KU.first > KU.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::Hit:
			sprite.setTextureRect(anchors[hit.first + currentFrame]);
			sprite.setOrigin(origins[hit.first + currentFrame]);
			if (currentFrame + hit.first < hit.second)
				currentFrame++;
			else if (onBoard) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
				lastHit = CharacterState::Default;
			}
			break;
		case CharacterState::Kick:
			sprite.setTextureRect(anchors[kick.first + currentFrame]);
			sprite.setOrigin(origins[kick.first + currentFrame]);
			if (currentFrame == 0) audioEventQueue.push("gaara_kick");
			if (currentFrame + kick.first < kick.second)
				currentFrame++;	
			else if (onBoard) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
				lastHit = CharacterState::Default;
			}
			break;
		default:
			break;
		}
		elapsedTime = 0.f;
		if (left)
			sprite.setScale(-1.f, 1.f); // 水平镜像，垂直保持不变
		else {
			sprite.setScale(1.f, 1.f);
		}
	}
	sprite.setPosition(position);
}