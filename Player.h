#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
class Player :
    public Character
{

public:
    void handleInput(sf::Event event);
    void useSkill();
};

