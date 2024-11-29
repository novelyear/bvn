#include "Gaara.h"

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