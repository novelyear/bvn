#include "keyMap.h"

std::unordered_map<bool, std::unordered_map<std::string, sf::Keyboard::Key>> key;

void initializeKeyMapping() {
    key[true]["A"] = sf::Keyboard::A;
    key[true]["D"] = sf::Keyboard::D;
    key[true]["K"] = sf::Keyboard::K;
    key[true]["J"] = sf::Keyboard::J;
    key[true]["L"] = sf::Keyboard::L;
    key[true]["W"] = sf::Keyboard::W;
    key[true]["S"] = sf::Keyboard::S;
    key[true]["U"] = sf::Keyboard::U;
    key[true]["I"] = sf::Keyboard::I;


    key[false]["A"] = sf::Keyboard::Left;
    key[false]["D"] = sf::Keyboard::Right;
    key[false]["K"] = sf::Keyboard::Numpad2;
    key[false]["J"] = sf::Keyboard::Numpad1;
    key[false]["L"] = sf::Keyboard::Numpad3;
    key[false]["W"] = sf::Keyboard::Up;
    key[false]["S"] = sf::Keyboard::Down;
    key[false]["U"] = sf::Keyboard::Numpad4;
    key[false]["I"] = sf::Keyboard::Numpad5;
}

