#pragma once
#include "Character.h"
#include <bits/stdc++.h>
#include "Map.h"
class Controller
{
private:
    Character* role; // ���˽�ɫ
    Character* target;     // ��ҽ�ɫ
public:
    Controller(Character* enemy, Character* player);

    void process(Map* map);
};

