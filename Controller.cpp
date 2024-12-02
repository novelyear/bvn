#include "Controller.h"

Controller::Controller(Character* enemy, Character* player): role(enemy), target(player) {}

void Controller::process(Map* map) {
    if (role->currentState == CharacterState::Flash ||
        role->currentState == CharacterState::Hit ||
        role->currentState == CharacterState::Kick) {
        return;
    }
    if (c.getElapsedTime().asSeconds() >= 3.f) {
        role->su();  // 每隔3秒调用su()
        c.restart();  // 重置计时器
    }
}

