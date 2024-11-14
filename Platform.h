#pragma once
#include <SFML/Graphics.hpp>
class Platform
{
	sf::FloatRect bound;
public:
	const sf::FloatRect & getBounds() const;
};

