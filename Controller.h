#pragma once
#include "Character.h"
#include <bits/stdc++.h>
#include "Map.h"
#include "Constants.h"

class AI {
public:
    virtual ~AI() {}
    virtual void process(Character* role, Character* target, Map* map) = 0;
};

class Controller
{
public:
    Character* role; // 敌人角色
    Character* target;     // 玩家角色
    sf::Clock c;
    Controller(Character* enemy, Character* player);
    std::unique_ptr<AI> ai;
    void process(Map* map);
};

class GaaraAI : public AI {
public:
    void process(Character* role, Character* target, Map* map) override;
};

class NarutoAI : public AI {
public:
    void process(Character* role, Character* target, Map* map) override;
};

