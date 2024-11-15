#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
class Player :
    public Character
{

public:
    Player();
    void handleMove();
    void handleInput(sf::Event event);
    void useSkill();
};

