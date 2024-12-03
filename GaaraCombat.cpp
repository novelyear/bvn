#include "Gaara.h"
#include "Constants.h"

void Gaara::u() {
	if (currentState != CharacterState::U) {
		currentState = CharacterState::U;
		currentFrame = 0;
		/*effects->u(position, left);*/
	}
}

void Gaara::ku() {
	if (currentState != CharacterState::KU) {
		currentState = CharacterState::KU;
		currentFrame = 0;
		jumpTimes = 3;
		velocity.y = 0;
	}
}

void Gaara::si() {
	if (currentState != CharacterState::SI_before &&
		currentState != CharacterState::SI_miss &&
		currentState != CharacterState::SI_after) {
		currentState = CharacterState::SI_before;
		currentFrame = 0;
	}
}

void Gaara::i() {
	if (currentState != CharacterState::I_before &&
		currentState != CharacterState::I_miss &&
		currentState != CharacterState::I_after) {
		currentState = CharacterState::I_before;
		currentFrame = 0;
	}
}
void Gaara::wu() {
	if (currentState != CharacterState::WU) {
		currentState = CharacterState::WU;
		currentFrame = 0;
	}
}

void Gaara::exertEffect(Character* enemy, int type) {
	if ((int)enemy->lastHit == type) return;
	if (enemy->currentState == CharacterState::S && enemy->chakra > CHAKRA_L) {
		enemy->chakra -= CHAKRA_L;
		return;
	}
	switch (type) { // 不能用自己的状态，U状态结束后特效仍然会在，要么给特效单独写一个？
	case (int)CharacterState::J1:
		enemy->gainVelocity({ this->left ? -0.3f : 0.3f, 0.f });
		enemy->lastHit = (CharacterState)type;
		enemy->currentState = CharacterState::Hit;
		break;
	case (int)CharacterState::J2:
		enemy->gainVelocity({0.f, -3.f});
		enemy->lastHit = (CharacterState)type;
		enemy->currentState = CharacterState::Hit;
		break;
	case (int)CharacterState::J3:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, 0.f });
		enemy->lastHit = (CharacterState)type;
		enemy->currentState = CharacterState::Kick;
		break;
	case (int)CharacterState::SJ:
		enemy->gainVelocity({ this->left ? -30.f : 30.f, 0.f });
		enemy->lastHit = (CharacterState)type;
		enemy->currentState = CharacterState::Kick;
		break;
	case (int)CharacterState::WJ:
		enemy->gainVelocity({ this->left ? -2.f : 2.f, 3.f });
		enemy->currentState = CharacterState::Kick;
		enemy->lastHit = (CharacterState)type;
		break;
	case (int)CharacterState::SU:
		enemy->gainVelocity({ this->left ? -0.5f : 0.5f, 0.f });
		enemy->currentState = CharacterState::Hit;
		break;
	case (int)CharacterState::KU:
		enemy->gainVelocity({ 0.f, TOLERANCE });
		enemy->currentState = CharacterState::Kick;
		enemy->lastHit = (CharacterState)type;
		break;
	case (int)CharacterState::U:
		enemy->gainVelocity({ this->left ? -0.5f : 0.5f, 0.f });
		enemy->currentState = CharacterState::Kick;
		enemy->lastHit = (CharacterState)type;
		break;
	case (int)CharacterState::WU:
		enemy->gainVelocity({ 0.f, -2.f });
		enemy->currentState = CharacterState::Hit;
		enemy->lastHit = (CharacterState)type;
		break;
	default:
		break;
	}
	enemy->currentFrame = 0;
}


