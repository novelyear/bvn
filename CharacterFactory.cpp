#include "CharacterFactory.h"

std::unique_ptr<Character> CharacterFactory::createCharacter(CharacterType type) {
    switch (type) {
    case CharacterType::Gaara:
        return std::make_unique<Gaara>();
    default:
        throw std::invalid_argument("Unknown character type");
    }
}