#include "Controller.h"
#include "Constants.h"

Controller::Controller(Character* enemy, Character* player): role(enemy), target(player) {
    if (role->name == CharacterType::Gaara) {
        ai = std::make_unique<GaaraAI>();
    }
    else if (role->name == CharacterType::NarutoS) {
        ai = std::make_unique<NarutoAI>();
    }
}

void Controller::process(Map* map) {
    if (role->currentState != CharacterState::Stand &&
        role->currentState != CharacterState::Running &&
        role->currentState != CharacterState::Jumping &&
        role->currentState != CharacterState::Fall &&
        role->currentState != CharacterState::S_Release &&
        role->currentState != CharacterState::Landed) {
        return;
    }

    if (c.getElapsedTime().asSeconds() < 0.3f) return; // 每x秒运行一次
    c.restart();

    if (ai) {
        ai->process(role, target, map); // 调用AI逻辑
    }
}

void NarutoAI::process(Character* role, Character* target, Map* map){
    // 先判断当前状况
    bool faceMe = !(target->left ^ (target->position.x > role->position.x));
    // 如果gaara放U或者SU， 跳
    if (faceMe && (target->currentState == CharacterState::U || target->currentState == CharacterState::SU)) {
        role->flash();
    }
    bool inSameHeight = fabs(role->position.y - target->position.y) < 50.f;
    int floorDiff = fabs(role->position.y - target->position.y) / 45.f;
    bool faceHim = !(role->left ^ (role->position.x > target->position.x));
    bool inSlopTop = faceHim && fabs(role->position.x - role->position.x) < 200.f &&
        fabs(role->position.y - target->position.y) < 100.f;
    bool farAway = faceHim && fabs(role->position.x - target->position.x) > 300.f;
    bool closeWithMe = faceHim && fabs(role->position.x - target->position.x) < 100.f;
    if (target->currentState == CharacterState::SJ) { // gaara的SJ，flash躲避，不能硬碰
        if (target->currentFrame > 25) role->sj();
        else if (role->qi >= MAX_QI && target->currentFrame > 34) role->wi();
        else role->flash();
    }
    if (target->currentState == CharacterState::KU) {
        if (role->qi > MAX_QI) role->wi();
        else {
            role->sj();
        }
    }
    // 如果gaara正被我打
    if (target->currentState == CharacterState::Hit) { 
        // 连
        if (role->currentState == CharacterState::WU) {
            role->wuu();
        }
        else if (role->currentState == CharacterState::SJ) {
            role->ku(); 
        }
        else if (role->currentState == CharacterState::WJ) {
            if (rand() % 2) {
                role->wu();
            }
            else {
                role->wj();
            }
        }
        else if (role->currentState == CharacterState::U) {
                role->wj();
        }
        else if (role->qi > MAX_QI && target->currentState != CharacterState::Kick) {
            role->wi();
        }
        return;
    }
    if (closeWithMe && role->qi >= MAX_QI * 3) { // 有大就放，青春
        role->si();
    }
    if (closeWithMe && !faceMe) {
        role->suu();
    }
}

void GaaraAI::process(Character* role, Character* target, Map* map) {
    // gaara没有位移技能，需要多跑动

    //if (敌方是kick状态) {
    //    move+jump+down拉近距离
    //}


    //if (敌方在同一高度) {
    //    if (敌方在攻击) {
    //        flash();
    //    }

    //    if (距离极近) sj();
    //    else if (有大且距离适中) {
    //        if (敌方处于u、flash、run状态) sj();
    //        else wi();
    //    }
    //    else 
    //        u() 或者 su()
    //}
    //else {
    //    if (敌人正好在上方对角线一层) wj();
    //    else if (有大) {
    //        i(); 或者 si();
    //    }
    //    else
    //        wu();
    //}
}
//

//// 如果不在同一高度
//if (!inSameHeight) {
//    if (!target->canTouch()) {
//        if (role->qi > MAX_QI)
//            role->wi();
//        else if (floorDiff >= 2)
//            role->jump();
//    }
//    else if (inSlopTop) {
//        if (target->position.y < role->position.y) role->wu();
//        else if (role->qi > MAX_QI) role->ki();
//        else role->ku();
//    }
//    else
//        if (rand() % 2) {
//            role->sj();
//        }
//        else {
//            role->wi();
//        }
//}
//else { // 在同一高度
//    if (farAway) {
//        if (role->qi > MAX_QI) role->i();
//        else {
//            role->suu();
//        }
//    }
//    else if (closeWithMe) {
//        if (role->qi > MAX_QI) {
//            if (role->qi >= MAX_QI * 3) role->si();
//            else role->i();
//        }
//        else {
//            role->suu();
//        }
//    }
//}