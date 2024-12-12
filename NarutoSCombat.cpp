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
		enemy->chakra -= CHAKRA_L / 2;
		this->qi += 5;
		enemy->qi += 4;
		enemy->health -= 2;
		return;
	}
	switch (e->currentState) {
	case EffectState::KI_after:
		enemy->gainVelocity({0.f, -GRAVITY});
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		if (e->currentFrame > 13) {
			enemy->gainVelocity({ left ? -7.f : 7.f, -8.f });
			enemy->health -= 31; // 伤害
			enemy->qi += 15;
			enemy->currentState = CharacterState::Kick;audioEventQueue.push("kick");
		}
		break;
	default:
		break;
	}
	enemy->currentFrame = 0;
	if (enemy->currentState == CharacterState::Kick) {
		eventQueue.push(EventType::SkillHit); // 击飞触发震屏
		pauseEventQueue.push({ EventType::SkillHit, this, PAUSE_KICK, false }); // 击飞触发全局暂停
	}
}

void NarutoS::exertEffect(Character* enemy) {
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
		enemy->gainVelocity({ this->left ? -0.1f : 0.1f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->health -= 3; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		break;
	case CharacterState::J2:
		enemy->gainVelocity({ this->left ? -0.1f : 0.1f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->health -= 3; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		break;
	case CharacterState::J3:
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 3; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		eventQueue.push(EventType::SkillHit);
		pauseEventQueue.push({ EventType::SkillHit, this, PAUSE_KICK, false });
		break;
	case CharacterState::J4:
		enemy->gainVelocity({ this->left ? -1.5f : 1.5f, -6.f });
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 6; // 伤害
		this->qi += 12; // 攻击者获得更多气
		enemy->qi += 6;
		eventQueue.push(EventType::SkillHit);
		pauseEventQueue.push({ EventType::SkillHit, this, PAUSE_KICK, false });
		break;
	case CharacterState::KJ:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, 0.f });
		enemy->lastHit = this->currentState;
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 3; // 伤害
		this->qi += 8; // 攻击者获得更多气
		enemy->qi += 4;
		break;
	case CharacterState::SJ:
		enemy->gainVelocity({ this->left ? -0.1f : 0.1f, 0.f });
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 2; // 伤害
		this->qi += 2; // 攻击者获得更多气
		enemy->qi += 1;
		break;
	case CharacterState::WJ:
		enemy->gainVelocity({ this->left ? -2.f : 2.f, -7.f });
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 8; // 伤害
		this->qi += 9; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::SU:
		enemy->gainVelocity({ this->left ? -1.5f : 1.5f, 0.f });
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 6; // 伤害
		this->qi += 6; // 攻击者获得更多气
		enemy->qi += 3;
		enemy->lastHit = this->currentState;
		eventQueue.push(EventType::SkillHit);
		pauseEventQueue.push({ EventType::SkillHit, this, PAUSE_KICK, false });
		break;
	case CharacterState::SUU:
		enemy->gainVelocity({ this->left ? -5.5f : 5.5f, 0.f });
		enemy->health -= 6; // 伤害
		this->qi += 6; // 攻击者获得更多气
		enemy->qi += 3;
		enemy->currentState = CharacterState::Kick;audioEventQueue.push("kick");
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::KU:
		enemy->gainVelocity({ this->left ? -1.f : 1.f, TOLERANCE });
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 4; // 伤害
		this->qi += 4; // 攻击者获得更多气
		enemy->qi += 2;
		break;
	case CharacterState::U_after:
		enemy->gainVelocity({ this->left ? -2.f : 2.f, -7.f });
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 9; // 伤害
		this->qi += 9; // 攻击者获得更多气
		enemy->qi += 4;
		enemy->lastHit = this->currentState;
		eventQueue.push(EventType::SkillHit); 
		pauseEventQueue.push({ EventType::SkillHit, this, PAUSE_KICK, false }); 
		break;
	case CharacterState::WU:
		enemy->gainVelocity({ this->left ? -1.5f : 1.5f, -2.5f });
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 4; // 伤害
		this->qi += 4; // 攻击者获得更多气
		enemy->qi += 2;
		break;
	case CharacterState::WUU:
		enemy->gainVelocity({ this->left ? -4.5f : 4.5f, -8.5f });
		enemy->currentState = CharacterState::Kick;audioEventQueue.push("kick");
		enemy->health -= 5; // 伤害
		this->qi += 5; // 攻击者获得更多气
		enemy->qi += 2;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::WI_before:
		enemy->currentState = CharacterState::Kick;audioEventQueue.push("kick");
		enemy->gainVelocity({ this->left ? -10.f : 10.f, -8.f });
		enemy->health -= 26; // 伤害
		enemy->qi += 10;
		enemy->lastHit = this->currentState;
		break;
	case CharacterState::SI_before:
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		enemy->health -= 4; // 伤害
		this->qi += 1; // 攻击者获得更多气
		enemy->qi += 2;
		if (this->currentFrame > 74) {
			enemy->gainVelocity({ this->left ? -12.f : 12.f, -12.f });
			enemy->currentState = CharacterState::Kick;audioEventQueue.push("kick");
			enemy->health -= 30; // 伤害
			enemy->qi += 13;
			enemy->lastHit = this->currentState;
		}
		break;
	case CharacterState::I_before:
		enemy->currentState = CharacterState::Hit;audioEventQueue.push("hit");
		if (this->currentFrame > 44) {
			enemy->gainVelocity({ this->left ? -8.f : 8.f, -8.f });
			enemy->currentState = CharacterState::Kick;audioEventQueue.push("kick");
			enemy->health -= 26; // 伤害
			enemy->qi += 10;
			enemy->lastHit = this->currentState;
		}
		break;
	default:
		break;
	}
	enemy->currentFrame = 0;
	if (enemy->currentState == CharacterState::Kick) {
		eventQueue.push(EventType::SkillHit); // 击飞触发震屏
		pauseEventQueue.push({ EventType::SkillHit, this, PAUSE_KICK, false }); // 击飞触发全局暂停
	}
}