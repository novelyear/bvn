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
		currentState == CharacterState::Fall) {
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

void Character::update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) {
	updateCollisionWithEnemy(enemy);
	updateCollisionWithPlatform(platforms);
	updateDirection(enemy->position);
	updatePosition(view);
	updateSprite(deltaTime);
}

void Character::updatePosition(sf::View view) {
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	// 获取视图的当前边界
	float left = center.x - size.x / 2.f;
	float right = center.x + size.x / 2.f;


	position.x += velocity.x;
	velocity.x = 0;
	if (position.x <= left) {
		position.x = left;
	}
	else if (position.x >= right) {
		position.x = right;
	}

	if ((currentState == CharacterState::Jumping ||
		currentState == CharacterState::Fall ||
		currentState == CharacterState::Flash)
		&& velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}

	position.y += velocity.y;
	// 兜底机制
	if (position.y >= CHARACTER_BOTTOM) {
		position.y = CHARACTER_BOTTOM;  // 重置位置
		inAir = false;
		if (currentState != CharacterState::Running) {
			currentState = CharacterState::Stand;  // run和stand都需要platform
		}
		velocity.y = 0.f;  // 清除竖直速度
		jumpTimes = 0;  // 重置跳跃次数
	}
}

bool XOR(bool a, bool b) {
	return (a + b) % 2;
}

void Character::updateDirection(sf::Vector2f enemyPosition) {
	if (currentState != CharacterState::Stand) return;
	// 站立时，自动转向敌人所在方向
	if (XOR(left, enemyPosition.x < this->position.x)) {
		left = !left;
	}
}

void Character::updateCollisionWithPlatform(std::vector<Platform> platforms) {
	if (platforms.empty() || velocity.y < 0) return;
	bool onBoard = false;
	// 遍历所有platform，判断是否在上面
	for (const auto& platform : platforms) {
		sf::Vector2f platformStart = platform.startPosition;
		float platformWidth = platform.width;

		// 检测是否站在平台上
		if (position.y >= platformStart.y &&  // 位于平台高度
			position.y <= platformStart.y + TOLERANCE && // 允许小范围误差
			position.x >= platformStart.x && // 在平台范围内
			position.x <= platformStart.x + platformWidth) {
			onBoard = true;

			position.y = platformStart.y;  // 站在上面
			inAir = false;
			if (currentState != CharacterState::Running) {
				currentState = CharacterState::Stand;  // run和stand都需要platform
			}
			velocity.y = 0.f;  // 清除竖直速度
			jumpTimes = 0;  // 重置跳跃次数
			
			break;
		}
	}
	if (!onBoard && (currentState == CharacterState::Stand || currentState == CharacterState::Running)) {
		currentState = CharacterState::Jumping;
		currentFrame = 0;
	}
}

void separate(Character* p1, Character* p2) {
	// 默认已经重合
	float r = std::fabs(p1->position.x - p2->position.x);
	bool left = p1->position.x < p2->position.x; // p1在左边就获得负的加速度
	float acceleration = REPULSION / r;
	p1->gainVelocity({ acceleration * left ? -0.2f : 0.2f, 0 });
	p2->gainVelocity({ acceleration * left ? 0.2f : -0.2f, 0 });
}

void Character::updateCollisionWithEnemy(Character* enemy) {
	// 素材尺寸不一，如果设为属性避免重复计算，那在更新精灵时需要加判断，目前帧率溢出，可不优化
	sf::FloatRect playerRect = this->sprite.getLocalBounds();
	sf::FloatRect enemyRect = enemy->sprite.getLocalBounds();
	playerRect.left = this->position.x - playerRect.width / 2.f;
	playerRect.top = this->position.y - playerRect.height / 2.f;
	enemyRect.left = enemy->position.x - enemyRect.width / 2.f;
	enemyRect.top = enemy->position.y - enemyRect.height / 2.f;
	// 前提：不可能完全重合==>重合点归入一边即可
	// 似乎原游戏存在重量，人物相推速度变化不一致，有的减半，有的更慢
	// 这里都设置为一样的重量，如果有人物挡道，则速度减半
	if(!playerRect.intersects(enemyRect)) return;
	if (std::fabs(this->position.y - enemy->position.y) < TOLERANCE && this->velocity.x != 0.f) { // 同高度，水平碰撞
		this->velocity.x /= 4.f;
		enemy->gainVelocity({this->velocity.x, 0.f});
	}
	separate(this, enemy);
}

void Character::updateSprite(float deltaTime) {
	if (textures.empty()) return;
	elapsedTime += deltaTime;
	if (elapsedTime > PLAYER_FRAME) {
		switch (currentState) {
		case CharacterState::Stand:
			sprite.setTexture(textures[stand.first + currentFrame]);
			sprite.setOrigin(origins[stand.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (stand.second - stand.first);
			break;
		case CharacterState::Running:
			sprite.setTexture(textures[run.first + currentFrame]);
			sprite.setOrigin(origins[run.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (run.second - run.first);
			break;
		case CharacterState::Jumping:
			sprite.setTexture(textures[jumping.first + currentFrame]);
			sprite.setOrigin(origins[jumping.first + currentFrame]);
			currentFrame = (currentFrame + 1) % (jumping.second - jumping.first);
			break;
		case CharacterState::Flash:
			sprite.setTexture(textures[flashing.first + currentFrame]);
			sprite.setOrigin(origins[flashing.first + currentFrame]);
			currentFrame++;
			if (currentFrame + flashing.first > flashing.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			else {

			}
			break;
		case CharacterState::Fall:
			sprite.setTexture(textures[fall.first + currentFrame]);
			sprite.setOrigin(origins[fall.first + currentFrame]);
			if (currentFrame + fall.first < fall.second) currentFrame++;
		default:
			break;
		}
		elapsedTime = 0.f;
		// 设置纹理矩形为当前纹理的完整区域
		sf::Vector2u textureSize = sprite.getTexture()->getSize(); // 获取纹理尺寸
		sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
		if (left)
			sprite.setScale(-1.f, 1.f); // 水平镜像，垂直保持不变
		else {
			sprite.setScale(1.f, 1.f);
		}
	}
	sprite.setPosition(position);
}

void Character::gainVelocity(sf::Vector2f acceleration) {
	this->velocity += acceleration;
}



void Character::handleMove() {
	if (currentState == CharacterState::Flash) {
		return;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
		//return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveRight();
		//return;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = 0;  // 停止水平移动
		if (currentState == CharacterState::Running) {
			currentState = CharacterState::Stand;
			currentFrame = 0;
		}
		//return;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // 冲刺
		if(jumpTimes > 1) { //之后补充chakra机制限制冲刺次数，同时空中只能冲刺一次
			return;
		}
		flash();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // S：防御、下落、普攻3、大招3、远攻3
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			down();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			// 普攻3
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			// 大招3
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			// 远攻3
		}
		else {
			// 防御
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		jump();
		return;
	}
}

void Character::handleInput(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::K)
			jump();		
	}
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