#include "Factories.h"
#include "NarutoS.h"

std::unique_ptr<Character> CharacterFactory::createCharacter(CharacterType type, bool forEnemy) {
    switch (type) {
    case CharacterType::Gaara:
        if (forEnemy) {
            return std::make_unique<Gaara>((int)1); // 调用带参数的构造函数
        }
        else {
            return std::make_unique<Gaara>();  // 调用默认构造函数
        }
    case CharacterType::NarutoS:
        if (forEnemy) {
            return std::make_unique<NarutoS>((int)1); // 调用带参数的构造函数
        }
        else {
            return std::make_unique<NarutoS>();  // 调用默认构造函数
        }
    default:
        throw std::invalid_argument("Unknown character type");
    }
}

std::unique_ptr<Map> MapFactory::createMap(MapType type)
{
    switch (type) {
    case MapType::MR:
        return std::make_unique<MR>();  // 调用默认构造函数
    case MapType::VE:
        return std::make_unique<VE>();  // 调用默认构造函数
    default:
        throw std::invalid_argument("Unknown character type");
    }
}
