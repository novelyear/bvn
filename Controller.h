#pragma once
#include "Character.h"
#include <bits/stdc++.h>
#include "Map.h"
class Controller
{
private:
    Character* role; // 敌人角色
    Character* target;     // 玩家角色
public:
    Controller(Character* enemy, Character* player);

    void process(Map* map);
};

