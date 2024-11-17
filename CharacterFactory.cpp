#include "CharacterFactory.h"

std::unique_ptr<Character> CharacterFactory::createCharacter(CharacterType type, bool forEnemy) {
    switch (type) {
    case CharacterType::Gaara:
        if (forEnemy) {
            return std::make_unique<Gaara>((int)1); // ���ô������Ĺ��캯��
        }
        else {
            return std::make_unique<Gaara>();  // ����Ĭ�Ϲ��캯��
        }
    default:
        throw std::invalid_argument("Unknown character type");
    }
}
