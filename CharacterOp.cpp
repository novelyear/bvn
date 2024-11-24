#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"

Character::Character(){
	attackStage = 0;
	currentState = CharacterState::Stand;
	health = INIT_HEALTH;
	inAir = true;
	jumpTimes = 0;
	left = true;
	elapsedTime = PLAYER_FRAME;
	currentFrame = 0;
}

void Character::moveLeft() {
	if (currentState == CharacterState::Running || currentState == CharacterState::Stand) {
		left = true;
	}
	attackStage = 0;
	velocity.x = -MOVE_VELOCITY;
	if (currentState == CharacterState::Stand) {
		currentFrame = 0;
		currentState = CharacterState::Running;
	}
}
void Character::moveRight() {
	if (currentState == CharacterState::Running || currentState == CharacterState::Stand) {
		left = false;
	}
	attackStage = 0;
	velocity.x = MOVE_VELOCITY;
	if (currentState == CharacterState::Stand) {
		currentFrame = 0;
		currentState = CharacterState::Running;
	}
}
void Character::jump() {
	if (jumpTimes >= 2) {
		return;
	}
	else if (jumpTimes >= 1 && velocity.y <= LIMIT_V) return;
	jumpTimes++;
	velocity.y = JUMP_VELOCITY;
	inAir = true;
	std::cout << "jumped" << std::endl;
	if (currentState != CharacterState::Jumping) {
		currentFrame = 0;
		currentState = CharacterState::Jumping;
	}
}

void Character::down() {
	if (currentState == CharacterState::Stand || currentState == CharacterState::Running) {
		currentState = CharacterState::Jumping;
		currentFrame = 0;
		position.y += TOLERANCE + 0.01f;
	}
}

void Character::flash() {
	// 只有Onboard和空中一段跳时可以冲刺，消耗气，调用时已经判断气和跳跃
	if (currentState == CharacterState::Stand ||
		currentState == CharacterState::Jumping ||
		currentState == CharacterState::Fall ||
		currentState == CharacterState::Running) {
		velocity.x = left ? -FLASH_VELOCITY : FLASH_VELOCITY;
		currentState = CharacterState::Flash;
		currentFrame = 0;
		jumpTimes++;
		// TODO 减少气
	}
}

void Character::render(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Character::gainVelocity(sf::Vector2f acceleration) {
	this->velocity += acceleration;
}

void Character::loadResources(const std::string& directory, const std::string& rangeFile, const std::string& originFile) {
	// 区间
	std::map<std::string, std::pair<int, int>> ranges;
	std::ifstream rangeStream(rangeFile);
	if (!rangeStream.is_open()) {
		std::cerr << "Failed to open range file: " << rangeFile << std::endl;
		return;
	}

	std::string line;
	while (std::getline(rangeStream, line)) {
		std::istringstream iss(line);
		std::string name, rangeStr;
		if (std::getline(iss, name, '-') && std::getline(iss, rangeStr)) {
			int left, right;
			if (sscanf_s(rangeStr.c_str(), "[%d, %d]", &left, &right) == 2) {
				ranges[name] = { left, right }; // Convert to 0-based indexing
			}
		}
	}

	rangeStream.close();

	// 图片
	int maxIndex = 0;
	for (const auto& rangePair : ranges) {
		const auto& range = rangePair.second;
		maxIndex = std::max(maxIndex, range.second);
	}

	textures.resize(maxIndex + 1);
	for (int i = 1; i <= maxIndex; ++i) {
		sf::Texture texture;
		if (texture.loadFromFile(directory + "\\" + std::to_string(i) + ".png")) {
			textures[i] = std::move(texture); // 图号即是下标
		}
		else {
			std::cerr << "Failed to load texture: " << directory + "\\" + std::to_string(i) + ".png" << std::endl;
		}
	}

	// 分配对应区间
	auto mapRange = [&](const std::string& key, std::pair<int, int>& member) {
		if (ranges.find(key) != ranges.end()) {
			member = ranges[key];
		}
		else {
			std::cerr << "Range not found for: " << key << std::endl;
		}
	};

	mapRange("animation", animation);
	//mapRange("animation_win", animation_win);
	mapRange("fall", fall);
	mapRange("flash", flashing);
	mapRange("hit", hit);
	mapRange("I_after", I_after);
	mapRange("I_before", I_before);
	mapRange("I_miss", I_miss);
	mapRange("J1", J1);
	mapRange("J2", J2);
	mapRange("J3", J3);
	mapRange("jump", jumping);
	mapRange("kick", kick);
	mapRange("KJ", KJ);
	mapRange("KU", KU);
	mapRange("landed", landed);
	mapRange("run", run);
	mapRange("S", S);
	mapRange("SI_after", SI_after);
	mapRange("SI_before", SI_before);
	mapRange("SI_miss", SI_miss);
	mapRange("SJ", SJ);
	mapRange("stand", stand);
	mapRange("SU", SU);
	mapRange("U", U);
	mapRange("WI_after", WI_after);
	mapRange("WI_before", WI_before);
	mapRange("WI_miss", WI_miss);
	mapRange("WJ", WJ);
	mapRange("WU", WU);
	

	// 原点坐标
	std::ifstream originStream(originFile);
	if (!originStream.is_open()) {
		std::cerr << "Failed to open origin file: " << originFile << std::endl;
		return;
	}

	origins.resize(maxIndex + 1);
	while (std::getline(originStream, line)) {
		int id, x, y;
		if (sscanf_s(line.c_str(), "%d-(%d, %d)", &id, &x, &y) == 3) {
			if (id >= 1 && id <= static_cast<int>(origins.size())) {
				origins[id] = sf::Vector2f((float)x, (float)y); // 图号即是下标
			}
			else {
				std::cerr << "Origin out of range for ID: " << id << std::endl;
			}
		}
	}

	originStream.close();
}