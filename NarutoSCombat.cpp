#include "NarutoS.h"
#include "Constants.h"


void NarutoS::ku() {
	currentState = CharacterState::KU;
	currentFrame = 0;
	jumpTimes = 3;
	velocity.y = 0;
}

void NarutoS::u() {
	currentState = CharacterState::U;
	currentFrame = 0;
	velocity.x = left ? -5.f : 5.f;
}


void NarutoS::exertEffect(Character* enemy, Effect * e) {
	if ((int)enemy->lastHit == (int)e->currentState) {
		return;
	}
	if (enemy->currentState == CharacterState::S && enemy->chakra > CHAKRA_L) {
		enemy->chakra -= CHAKRA_L;
		return;
	}
	switch (e->currentState) {
	case EffectState::KI_after:
		enemy->gainVelocity({0.f, -GRAVITY});
		enemy->currentState = CharacterState::Hit;
		if (e->currentFrame > 13) {
			enemy->gainVelocity({ left ? -7.f : 7.f, -8.f });
			enemy->currentState = CharacterState::Kick;
		}
		break;
	default:
		break;
	}
	enemy->currentFrame = 0;
}

void NarutoS::exertEffect(Character* enemy) {
	if (enemy->lastHit == this->currentState) {
		return;
	}
	if (enemy->currentState == CharacterState::S && enemy->chakra > CHAKRA_L) {
		enemy->chakra -= CHAKRA_L;
		return;
	}
	switch (this->currentState) { // 不能用自己的状态，U状态结束后特效仍然会在，要么给特效单独写一个
	case CharacterState::J1:
		enemy->gainVelocity({ this->left ? -0.1f : 0.1f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::J2:
		enemy->gainVelocity({ this->left ? -0.1f : 0.1f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::J3:
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::J4:
		enemy->gainVelocity({ this->left ? -1.5f : 1.5f, -6.f });
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::KJ:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::SJ:
		enemy->gainVelocity({ this->left ? -0.1f : 0.1f, 0.f });
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::WJ:
		enemy->gainVelocity({ this->left ? -2.f : 2.f, -7.f });
		enemy->currentState = CharacterState::Hit;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::SU:
		enemy->gainVelocity({ this->left ? -1.5f : 1.5f, 0.f });
		enemy->currentState = CharacterState::Hit;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::SUU:
		enemy->gainVelocity({ this->left ? -5.5f : 5.5f, 0.f });
		enemy->currentState = CharacterState::Kick;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::KU:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, TOLERANCE });
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::U_after:
		enemy->gainVelocity({ this->left ? -2.f : 2.f, -7.f });
		enemy->currentState = CharacterState::Hit;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::WU:
		enemy->gainVelocity({ this->left ? -1.5f : 1.5f, -2.5f });
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::WUU:
		enemy->gainVelocity({ this->left ? -4.5f : 4.5f, -8.5f });
		enemy->currentState = CharacterState::Kick;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::WI_before:
		enemy->currentState = CharacterState::Kick;
		enemy->gainVelocity({ this->left ? -10.f : 10.f, -8.f });
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::SI_before:
		enemy->currentState = CharacterState::Hit;
		if (this->currentFrame > 74) {
			enemy->gainVelocity({ this->left ? -12.f : 12.f, -12.f });
			enemy->currentState = CharacterState::Kick;
			enemy->lastHit = this->currentState;
		}
		break;
	case CharacterState::I_before:
		enemy->currentState = CharacterState::Hit;
		if (this->currentFrame > 44) {
			enemy->gainVelocity({ this->left ? -8.f : 8.f, -8.f });
			enemy->currentState = CharacterState::Kick;
			enemy->lastHit = this->currentState;
		}
		break;
	default:
		break;
	}
	enemy->currentFrame = 0;
}