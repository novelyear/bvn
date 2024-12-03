#include "Controller.h"

Controller::Controller(Character* enemy, Character* player): role(enemy), target(player) {}

void Controller::process(Map* map) {
    if (role->currentState == CharacterState::Flash ||
        role->currentState == CharacterState::Hit ||
        role->currentState == CharacterState::Kick) {
        return;
    }
    if (c.getElapsedTime().asSeconds() >= 3.f) {
        if (role->currentState == CharacterState::Stand ||
            role->currentState == CharacterState::Running ||
            role->currentState == CharacterState::S)
        {
            role->wj();
        }
        c.restart();  // ÖØÖÃ¼ÆÊ±Æ÷
    }
}

