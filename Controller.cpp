#include "Controller.h"

Controller::Controller(Character* enemy, Character* player): role(enemy), target(player) {}

void Controller::process(Map* map) {
    // 根据玩家位置，决定敌人的行为
    
}

