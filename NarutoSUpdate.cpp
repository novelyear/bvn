#include "NarutoS.h"
#include "Constants.h"

void NarutoS::update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) {
	updateSprite(deltaTime, enemy->position);
	// 敌人与攻击特效的碰撞
	updateCollisionWithEffect(enemy);
	updateCollisionWithPlatform(platforms);
	updateCollisionWithEnemy(enemy);
	updatePosition(view);
	updateDirection(enemy->position);
	effects->update(deltaTime, view);
	defaultEffects->update(deltaTime, view);
	cUI->update(this, view);
	// chakra更新，暂时写在这里
	if (currentState != CharacterState::Flash && currentState != CharacterState::S) {
		chakra++;
		if (chakra >= MAX_CHAKRA) {
			chakra = MAX_CHAKRA;
		}
	}
	if (qi > MAX_QI * 3) {
		qi = MAX_QI * 3;
	}
}

void NarutoS::updateCollisionWithEnemy(Character* enemy) {
	// 敌方冲刺状态和击飞状态不检测；
	// 己方冲刺状态无敌，不检测
	if (currentState == CharacterState::Flash || currentState == CharacterState::Kick ||
		enemy->currentState == CharacterState::Flash || enemy->currentState == CharacterState::Kick) {
		return;
	}
	// 自己的Rect应该只包括自己的身体，不能包括特效，比如特效被打到，不能被认定为被打到。
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
	playerRect.top = this->position.y - playerRect.height;
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
	if (hitTimer.getElapsedTime().asSeconds() < HIT_INTERVAL) { // 每 HIT_INTERVAL 秒受击判断一次
		return;
	}
	hitTimer.restart(); // 重设计时器
	// 翻译：敌人的特效与自己的本体有碰撞 & 敌人面向本体 & 敌人正在攻击 = 被打到了
	bool beAttacked = SameOr(enemy->left, this->position.x <= enemy->position.x) && !enemy->canTouch();
	if (beAttacked) {
		if (currentState == CharacterState::S) {
			chakra -= 10;
			return;
		}
		this->real ? printf("I'm hited\n") : printf("he is hitted\n");
		enemy->exertEffect(this);
	}
}

void NarutoS::updateSprite(float deltaTime, sf::Vector2f enemyPosition) {
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
			if (currentFrame == 0) {
				defaultEffects->run(this->position, EffectState::Landed_ash, true);
			}
			currentFrame++;
			if (currentFrame + landed.first > landed.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::Flash:
			sprite.setTextureRect(anchors[flashing.first + currentFrame]);
			sprite.setOrigin(origins[flashing.first + currentFrame]);
			if (currentFrame == 0) {
				defaultEffects->run(this->position, this->inAir ? EffectState::Flash_air : EffectState::Flash_ash, this->left);
			}
			currentFrame++;
			if (currentFrame + flashing.first > flashing.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::Fall:
			sprite.setTextureRect(anchors[fall.first + currentFrame]);
			sprite.setOrigin(origins[fall.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (fall.second - fall.first);
			break;
		case CharacterState::J1:
			sprite.setTextureRect(anchors[J1.first + currentFrame]);
			sprite.setOrigin(origins[J1.first + currentFrame]);
			if (currentFrame == 0) position.x += left ? -15.f : 15.f; // 0.3和Combat的统一
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
			if (currentFrame == 0) position.x += left ? -15.f : 15.f; // 
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
			currentFrame++;
			if (currentFrame + J3.first > J3.second) {
				if (attackStage > 3) {
					currentState = CharacterState::J4;
					currentFrame = 0;
				}
				else {
					currentState = CharacterState::Stand;
					currentFrame = 0;
					attackStage = 0;
				}
			}
			break;
		case CharacterState::J4:
			sprite.setTextureRect(anchors[J4.first + currentFrame]);
			sprite.setOrigin(origins[J4.first + currentFrame]);
			currentFrame++;
			if (currentFrame + J4.first > J4.second) {
				attackStage = 0;
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KJ:
			sprite.setTextureRect(anchors[KJ.first + currentFrame]);
			sprite.setOrigin(origins[KJ.first + currentFrame]);
			if (currentFrame == 0) position.x += left ? -20.f : 20.f; // 
			currentFrame++;
			if (currentFrame + KJ.first > KJ.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::SJ:
			sprite.setTextureRect(anchors[SJ.first + currentFrame]);
			sprite.setOrigin(origins[SJ.first + currentFrame]);
			if (currentFrame == 1) audioEventQueue.push("narutoS_SJ");
			currentFrame++;
			if (currentFrame == 5) {
				float offset = -35.f;
				this->position = { enemyPosition.x, enemyPosition.y + offset };
			}
			if (currentFrame + SJ.first > SJ.second) {
				currentState = CharacterState::Fall;
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
		case CharacterState::SUU:
			sprite.setTextureRect(anchors[SUU.first + currentFrame]);
			sprite.setOrigin(origins[SUU.first + currentFrame]);
			if (currentFrame == 3) audioEventQueue.push("narutoS_SUU");
			currentFrame++;
			if (currentFrame + SUU.first > SUU.second) {
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

			if (currentFrame > 4 && currentFrame < 36) {
				position.x += left ? -3.f : 3.f;
				position.y -= 40.f / (currentFrame - 4) / 2;
			}

			if (currentFrame + WU.first > WU.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::WUU:
			sprite.setTextureRect(anchors[WUU.first + currentFrame]);
			sprite.setOrigin(origins[WUU.first + currentFrame]);
			currentFrame++;
			if (currentFrame > 6 && currentFrame < 17) {
				position.x += left ? -3.f : 3.f;
				position.y -= 3.f;
			}
			if (currentFrame + WUU.first > WUU.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::WI_before:
			sprite.setTextureRect(anchors[WI_before.first + currentFrame]);
			sprite.setOrigin(origins[WI_before.first + currentFrame]);
			if (currentFrame == 0) {
				pauseEventQueue.push({ EventType::UltimateSkill, this, 4.5f, true });
				audioEventQueue.push("narutoS_WI");
				defaultEffects->run(position, EffectState::I_effect, this->left);
			}
			currentFrame++;
			if (currentFrame == 60) {
				sf::Vector2f offset = { this->left ? 45.f : -45.f, -90.f };
				this->position = enemyPosition + offset;
			}
			if (currentFrame + WI_before.first > WI_before.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::SI_before:
			sprite.setTextureRect(anchors[SI_before.first + currentFrame]);
			sprite.setOrigin(origins[SI_before.first + currentFrame]);
			if (currentFrame == 0) {
				pauseEventQueue.push({ EventType::UltimateSkill, this, 2.5f, true });
				audioEventQueue.push("narutoS_SI1");
				defaultEffects->run(position, EffectState::I_effect, this->left);
			}
			if (currentFrame == 60) {
				audioEventQueue.push("narutoS_SI2");
			}
			currentFrame++;
			if (currentFrame + SI_before.first > SI_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::I_before:
			sprite.setTextureRect(anchors[I_before.first + currentFrame]);
			sprite.setOrigin(origins[I_before.first + currentFrame]);
			if (currentFrame == 0) {
				pauseEventQueue.push({ EventType::UltimateSkill, this, 2.2f, true });
				audioEventQueue.push("narutoS_I");
				defaultEffects->run(position, EffectState::I_effect, this->left);
			}
			currentFrame++;
			if (currentFrame == 25) {
				velocity.x = left ? -5.f : 5.f;
			}
			if (currentFrame + I_before.first > I_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KI_before: // 人物不存在before、after、miss，为了统一，状态名加上before，实际的anchor、origin仍然仅为KI
			sprite.setTextureRect(anchors[KI.first + currentFrame]);
			sprite.setOrigin(origins[KI.first + currentFrame]);
			if (currentFrame == 0) {
				pauseEventQueue.push({ EventType::UltimateSkill, this, 4.5f, true });
				audioEventQueue.push("narutoS_KI");
				defaultEffects->run(position, EffectState::I_effect, this->left);
			}
			currentFrame++;
			if (currentFrame == 62) {
				sf::Vector2f offset = { 0.f, -50.f };
				effects->run(this->position + offset, EffectState::KI_before, this->left);
			}
			if (currentFrame + KI.first > KI.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::U:
			sprite.setTextureRect(anchors[U.first + currentFrame]);
			sprite.setOrigin(origins[U.first + currentFrame]);
			if (currentFrame == 0) {
				audioEventQueue.push("narutoS_U");
			}
			currentFrame++;
			if (U.second - currentFrame < U.first) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::U_after:
			sprite.setTextureRect(anchors[U_after.first + currentFrame]);
			sprite.setOrigin(origins[U_after.first + currentFrame]);
			currentFrame++;
			if (U_after.second - currentFrame < U_after.first) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KU:
			sprite.setTextureRect(anchors[KU.first + currentFrame]);
			sprite.setOrigin(origins[KU.first + currentFrame]);
			currentFrame++;
			if (currentFrame > 8) {
				velocity.y = MAX_FALLING_VELOCITY;
				velocity.x = this->left ? -MOVE_VELOCITY : MOVE_VELOCITY;
			}
			if (currentFrame + KU.first > KU.second) {
				currentFrame -= 6; // 回退6帧，维持螺旋丸
			}
			break;
		case CharacterState::KU_down:
			sprite.setTextureRect(anchors[KU_down.first + currentFrame]);
			sprite.setOrigin(origins[KU_down.first + currentFrame]);
			currentFrame++;
			if (currentFrame + KU_down.first > KU_down.second) {
				currentState = CharacterState::Stand;
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
			if (currentFrame + kick.first < kick.second)
				currentFrame++;
			else if (onBoard) { // 落地了才能脱离Kick状态
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