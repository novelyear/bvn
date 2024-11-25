#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"

void Character::j1(){
	currentState = CharacterState::J1;
	currentFrame = 0;
	attackStage = 1;
}

void Character::j2() {
	attackStage = 2;
}

void Character::j3() {
	attackStage = 3;
}

void Character::kj() {
	currentState = CharacterState::KJ;
	currentFrame = 0;
	velocity.y = 0;
	jumpTimes = 3; // 空中攻击后无法再二段跳
}

void Character::sj() {
	currentState = CharacterState::SJ;
	currentFrame = 0;
}

void Character::su() {
	currentState = CharacterState::SU;
	currentFrame = 0;
}

void Character::s() {
	if (currentState != CharacterState::S) {
		currentFrame = 0;
		currentState = CharacterState::S;
	}
}

void Character::s_release() {
	currentState = CharacterState::S_Release;
	currentFrame = 0;
}

void Character::wj() {
	currentState = CharacterState::WJ;
	currentFrame = 0;
}

void Character::wi() {
	currentState = CharacterState::WI_before;
	currentFrame = 0;
}