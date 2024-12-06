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
	// chakra更新，暂时写在这里
	if (currentState != CharacterState::Flash && currentState != CharacterState::S) {
		chakra++;
		if (chakra >= MAX_CHAKRA) {
			chakra = MAX_CHAKRA;
		}
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
			if (currentFrame + WU.first > WU.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::WI_before:
			sprite.setTextureRect(anchors[WI_before.first + currentFrame]);
			sprite.setOrigin(origins[WI_before.first + currentFrame]);
			currentFrame++;
			if (currentFrame + WI_before.first > WI_before.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::SI_before:
			sprite.setTextureRect(anchors[SI_before.first + currentFrame]);
			sprite.setOrigin(origins[SI_before.first + currentFrame]);
			currentFrame++;
			if (currentFrame + SI_before.first > SI_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::I_before:
			sprite.setTextureRect(anchors[I_before.first + currentFrame]);
			sprite.setOrigin(origins[I_before.first + currentFrame]);
			currentFrame++;
			if (currentFrame + I_before.first > I_before.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KI:
			sprite.setTextureRect(anchors[KI.first + currentFrame]);
			sprite.setOrigin(origins[KI.first + currentFrame]);
			currentFrame++;
			if (currentFrame + KI.first > KI.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::U:
			sprite.setTextureRect(anchors[U.first + currentFrame]);
			sprite.setOrigin(origins[U.first + currentFrame]);
			currentFrame++;
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