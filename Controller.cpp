#include "Controller.h"

Controller::Controller(Character* enemy, Character* player): role(enemy), target(player) {}

void Controller::process(Map* map) {
    if (c.getElapsedTime().asSeconds() >= 3.f) {
        role->su();  // ÿ��3�����su()
        c.restart();  // ���ü�ʱ��
    }
}

