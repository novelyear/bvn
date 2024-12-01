#pragma once
#include "Character.h"
#include <bits/stdc++.h>
#include "Map.h"
class Controller
{
public:
    Character* role; // 敌人角色
    Character* target;     // 玩家角色
    sf::Clock c;
    Controller(Character* enemy, Character* player);

    void process(Map* map);
};

