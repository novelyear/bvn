#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Character.h"

class Character;

class CharacterUI {
public:
    CharacterUI();
    void loadResources();
    sf::Vector2f getViewTopLeft(const sf::View& view) const;
    void update(Character* c, const sf::View& view);
    void render(sf::RenderWindow& window);

private:
    std::unordered_map<std::string, sf::Texture> textures; // 存储纹理
    std::unordered_map<std::string, sf::Sprite> fixedSprites; // 固定UI元件
    std::unordered_map<std::string, sf::Sprite> dynamicSprites; // 动态UI元件

    sf::Sprite& getSprite(const std::string& key);
    sf::Vector2f convertToUISpace(const sf::Vector2f& relativePosition);
};

