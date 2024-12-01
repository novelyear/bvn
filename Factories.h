#pragma once
#include "Character.h"
#include "Gaara.h"
#include "Map.h"
class CharacterFactory {
public:
	static std::unique_ptr<Character> createCharacter(CharacterType type, bool forEnemy);
};

class MapFactory {
public:
	static std::unique_ptr<Map> createMap(MapType type);
};

