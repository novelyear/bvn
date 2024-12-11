#include "Gaara.h"
#include "Constants.h"

void Gaara::sj() {
	if (currentState != CharacterState::SJ) {
		this->position.x += left ? -5.f : 5.f;
		currentState = CharacterState::SJ;
		currentFrame = 0;
	}
}

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
	if (qi < MAX_QI * 3) return;
	if (currentState != CharacterState::SI_before &&
		currentState != CharacterState::SI_miss &&
		currentState != CharacterState::SI_after) {
		currentState = CharacterState::SI_before;
		currentFrame = 0;
		qi = 0;
	}
}

void Gaara::i() {
	if (qi < MAX_QI) return;
	if (currentState != CharacterState::I_before &&
		currentState != CharacterState::I_miss &&
		currentState != CharacterState::I_after) {
		currentState = CharacterState::I_before;
		currentFrame = 0;
		qi -= MAX_QI;
	}
}

void Gaara::wu() {
	if (currentState != CharacterState::WU) {
		currentState = CharacterState::WU;
		currentFrame = 0;
	}
}
// Gaara的打击效果
void Gaara::exertEffect(Character* enemy, Effect * e) {
	if ((int)enemy->lastHit == (int)e->currentState) {
		return;
	}
	if (enemy->currentState == CharacterState::S && enemy->chakra > CHAKRA_L) {
		enemy->chakra -= CHAKRA_L / 2;
		this->qi += 5;
		enemy->qi += 4;
		enemy->health -= 2;
		return;
	}
	switch (e->currentState) { 
	case EffectState::U:
		enemy->gainVelocity({ this->left ? -0.5f : 0.5f, 0.f });
		enemy->health -= 12; // 伤害
		this->qi += 10; // 攻击者获得更多气
		enemy->qi += 5;
		enemy->currentState = CharacterState::Kick;
		enemy->lastHit = (CharacterState)e->currentState;
		break;
	case EffectState::WU:
		enemy->gainVelocity({ 0.f, -6.f });
		enemy->health -= 8; // 伤害
		this->qi += 10; // 攻击者获得更多气
		enemy->qi += 5;
		enemy->currentState = CharacterState::Hit;
		enemy->lastHit = (CharacterState)e->currentState;
		break;
	case EffectState::SI_before:
		enemy->currentState = CharacterState::Hit;
		enemy->health -= 10; // 伤害
		enemy->qi += 4;
		break;
	case EffectState::SI_after:
		enemy->currentState = CharacterState::Default;
		enemy->position.y = e->position.y;
		enemy->health -= 5; // 伤害
		enemy->qi += 2;
		if (e->currentFrame > 98) {// 特效在 98 帧后爆炸，此时敌方可飞出，最终段伤害
			enemy->gainVelocity({ this->left ? -12.f : 12.f, -12.f });
			enemy->currentState = CharacterState::Kick;
			enemy->health -= 30; // 伤害
			enemy->qi += 18;
			enemy->lastHit = (CharacterState)e->currentState;
		}
		break;
	case EffectState::I_before:
		enemy->currentState = CharacterState::Hit;
		enemy->health -= 5; // 伤害
		enemy->qi += 3;
		break;
	case EffectState::I_after:
		enemy->currentState = CharacterState::Default;
		enemy->position.y = e->position.y - e->sprite.getOrigin().y / 2.f;
		enemy->health -= 4; // 伤害
		enemy->qi += 2;
		if (e->currentFrame > 57) { // 特效在 57 帧后爆炸，此时敌方可飞出，最终段伤害
			enemy->gainVelocity({ this->left ? -6.f : 6.f, -8.5f });
			enemy->health -= 15; // 伤害
			enemy->qi += 10;
			enemy->currentState = CharacterState::Kick;
			enemy->lastHit = (CharacterState)e->currentState;
		}
		break;
	default:
		break;
	}
	if (enemy->currentState == CharacterState::Kick) {
		eventQueue.push(EventType::SkillHit); // 击飞触发震屏
		pauseEventQueue.push({ EventType::SkillHit, this, 0.2f, false }); // 击飞触发全局暂停
	}
	enemy->currentFrame = 0;
}

void Gaara::exertEffect(Character* enemy) {
	if (enemy->lastHit == this->currentState) {
		return;
	}
	if (enemy->currentState == CharacterState::S && enemy->chakra > CHAKRA_L) {
		enemy->chakra -= CHAKRA_L / 2;
		this->qi += 5;
		enemy->qi += 4;
		enemy->health -= 2;
		return;
	}
	switch (this->currentState) { // 不能用自己的状态，U状态结束后特效仍然会在，要么给特效单独写一个
	case CharacterState::J1:
		enemy->gainVelocity({ this->left ? -0.3f : 0.3f, 0.f });
		enemy->health -= 2; // 伤害
		this->qi += 5; // 攻击者获得更多气
		enemy->qi += 2;
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::J2:
		enemy->gainVelocity({ 0.f, -5.f });
		enemy->lastHit = this->currentState;
		enemy->health -= 4; // 伤害
		this->qi += 6; // 攻击者获得更多气
		enemy->qi += 3;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::J3:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, 0.f });
		enemy->health -= 5; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Kick;
		break;
	case CharacterState::KJ:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, TOLERANCE });
		enemy->lastHit = this->currentState;
		enemy->health -= 4; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->currentState = CharacterState::Hit;
		break;
	case CharacterState::SJ:
		enemy->gainVelocity({ this->left ? -8.5f : 8.5f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->health -= 17; // 伤害
		this->qi += 14; // 攻击者获得更多气
		enemy->qi += 7;
		enemy->currentState = CharacterState::Kick;
		break;
	case CharacterState::WJ:
		enemy->gainVelocity({ this->left ? -2.f : 2.f, -7.f });
		enemy->currentState = CharacterState::Kick;
		enemy->health -= 14; // 伤害
		this->qi += 12; // 攻击者获得更多气
		enemy->qi += 6;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::SU:
		enemy->gainVelocity({ this->left ? -0.5f : 0.5f, 0.f });
		enemy->currentState = CharacterState::Hit;
		enemy->health -= 2; // 伤害
		this->qi += 2; // 攻击者获得更多气
		enemy->qi += 1;
		break;
	case CharacterState::KU:
		enemy->gainVelocity({ 0.f, TOLERANCE });
		enemy->currentState = CharacterState::Kick;
		enemy->health -= 9; // 伤害
		this->qi += 10; // 攻击者获得更多气
		enemy->qi += 5;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::U:
		enemy->gainVelocity({ this->left ? -0.5f : 0.5f, 0.f });
		enemy->currentState = CharacterState::Kick;
		enemy->health -= 10; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::WI_before:
		enemy->currentState = CharacterState::Hit;
		if (this->currentFrame > 33) {  // 33 帧后，彻底被埋住
			enemy->currentState = CharacterState::Default;
			enemy->health -= 4; // 伤害
			enemy->qi += 1;
		}
		if (this->currentFrame > 46) {
			this->currentState = CharacterState::WI_after;
			this->currentFrame = 0;
		}
		break;
	case CharacterState::WI_after:
		enemy->currentState = CharacterState::Kick;
		enemy->gainVelocity({ 0.f, 8.f });
		enemy->health -= 20; // 伤害
		enemy->qi += 10; 
		break;
	default:
		break;
	}
	if (enemy->currentState == CharacterState::Kick) {
		eventQueue.push(EventType::SkillHit); // 击飞触发震屏
		pauseEventQueue.push({ EventType::SkillHit, this, 0.2f, false }); // 击飞触发全局暂停
	}
	enemy->currentFrame = 0;
}