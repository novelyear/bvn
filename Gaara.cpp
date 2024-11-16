#include "Gaara.h"
#include <bits/stdc++.h>
#include "Constants.h"

Gaara::Gaara() : Character() {
	left = true;
}

void Gaara::loadImage() {
	for (int i = 1; i <= 4; ++i) {
		// 构造文件名
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			standTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 11; i <= 16; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			runningTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 18; i <= 21; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			jumpingTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 23; i <= 24; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			hitTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	for (int i = 25; i <= 28; ++i) {
		std::string filename = "access/gaara/gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			kickTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	sprite.setTexture(standTextures[0]);
}

void Gaara::update(float deltaTime) {
	updatePosition();

	// 设置原点到底部中心
	sf::FloatRect bounds = sprite.getLocalBounds();
	float width = bounds.width;
	float height = bounds.height;
	sprite.setOrigin(width / 2.f, height);  // 底部中心是水平中心 + 垂直底部

	sprite.setPosition(position);
}

void Gaara::handleMove()
{
}

void Gaara::takeDamage(int amount) {

}

void Gaara::handleInput(sf::Event event) {

}

void Gaara::useSkill()
{
}
