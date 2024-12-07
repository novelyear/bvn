#include "NarutoS.h"
#include "Constants.h"
void NarutoS::ku() {
	currentState = CharacterState::KU;
	currentFrame = 0;
	jumpTimes = 3;
	velocity.y = 0;
}

void NarutoS::exertEffect(Character* enemy, Effect * e) {

}

void NarutoS::exertEffect(Character* enemy) {

}