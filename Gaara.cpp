#include "Gaara.h"
#include <bits/stdc++.h>
#include "Constants.h"

Gaara::Gaara() : Character() {
	left = false;
	position = { 100.f, GROUND };
	loadImage();
}

Gaara::Gaara(int flag) : Character() {
	left = true;
	position = { 300.f, GROUND };
	loadImage();
}

void Gaara::loadImage() {
	// 站立
	for (int i = 1; i <= 4; ++i) {
		// 构造文件名
		std::string filename = "access\\gaara\\gaara" + std::to_string(i) + ".png";
		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			standTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	// 跑动
	for (int i = 11; i <= 16; ++i) {
		std::string filename = "access\\gaara\\gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			runningTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	// 跃起
	for (int i = 18; i <= 21; ++i) {
		std::string filename = "access\\gaara\\gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			jumpingTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	// 受击
	for (int i = 23; i <= 24; ++i) {
		std::string filename = "access\\gaara\\gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			hitTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
	// 击飞
	for (int i = 25; i <= 28; ++i) {
		std::string filename = "access\\gaara\\gaara" + std::to_string(i) + ".png";

		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			kickTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filename << std::endl;
		}
	}
}

void Gaara::update(float deltaTime, sf::View view, sf::FloatRect enemyPosition) {
	updatePosition(view);
	updateSprite(deltaTime);
	updateDirection(enemyPosition);
}

void Gaara::updateSprite(float deltaTime) {
	elapsedTime += deltaTime;
	if (elapsedTime > PLAYER_FRAME) {
		switch (currentState) {
			case CharacterState::Stand:
				sprite.setTexture(standTextures[currentFrame]);
				currentFrame = (currentFrame + 1) % standTextures.size();
				break;
			case CharacterState::Running:
				sprite.setTexture(runningTextures[currentFrame]);
				currentFrame = (currentFrame + 1) % runningTextures.size();
				break;
			case CharacterState::Jumping:
				sprite.setTexture(jumpingTextures[currentFrame]);
				if (currentFrame < jumpingTextures.size() - 1) currentFrame++;
				break;
			default:
				break;
		}
		elapsedTime = 0.f;
		// 设置纹理矩形为当前纹理的完整区域
		sf::Vector2u textureSize = sprite.getTexture()->getSize(); // 获取纹理尺寸
		sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
		if(left)
			sprite.setScale(-1.f, 1.f); // 水平镜像，垂直保持不变
		else {
			sprite.setScale(1.f, 1.f); 
		}
	}
	// 设置原点到底部中心
	sf::FloatRect bounds = sprite.getLocalBounds();
	float width = bounds.width;
	float height = bounds.height;
	sprite.setOrigin(width / 2.f, height);  // 底部中心是水平中心 + 垂直底部
	sprite.setPosition(position);
}

void Gaara::takeDamage(int amount) {

}

void Gaara::useSkill() {
}
