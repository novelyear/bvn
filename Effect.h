#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class Effect
{
private:
	float duration;
	sf::Vector2f position;
	sf::Sprite sprite;
public:
	void update();
	void render(sf::RenderWindow window);
};

