#include "CharacterFactory.h"

std::unique_ptr<Character> CharacterFactory::createCharacter(CharacterType type, bool forEnemy) {
    switch (type) {
    case CharacterType::Gaara:
        if (forEnemy) {
            return std::make_unique<Gaara>((int)1); // 调用带参数的构造函数
        }
        else {
            return std::make_unique<Gaara>();  // 调用默认构造函数
        }
    default:
        throw std::invalid_argument("Unknown character type");
    }
}
