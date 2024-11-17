#pragma once
#include "Character.h"
#include "Gaara.h"
class CharacterFactory {
public:
	static std::unique_ptr<Character> createCharacter(CharacterType type, bool forEnemy);
};

