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

void Character::render(sf::RenderWindow& window) {
	sf::Sprite test;
	test.setTexture(standTextures[0]);
	test.setPosition({ LEFT_BORDER + 100.f, GROUND });
	window.draw(test);
	window.draw(sprite);
}

void Character::updatePosition(sf::View view) {
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	// ��ȡ��ͼ�ĵ�ǰ�߽�
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

	if (currentState == CharacterState::Jumping && velocity.y <= MAX_FALLING_VELOCITY) {
		velocity.y += GRAVITY;
	}

	position.y += velocity.y;
	// ���׻���
	if (position.y >= CHARACTER_BOTTOM) {
		position.y = CHARACTER_BOTTOM;  // ����λ��
		inAir = false;
		if (currentState != CharacterState::Running) {
			currentState = CharacterState::Stand;  // run��stand����Ҫplatform
		}
		velocity.y = 0.f;  // �����ֱ�ٶ�
		jumpTimes = 0;  // ������Ծ����
	}
}

bool XOR(bool a, bool b) {
	return (a + b) % 2;
}

void Character::updateDirection(sf::Vector2f enemyPosition) {
	if (currentState != CharacterState::Stand) return;
	// վ��ʱ���Զ�ת��������ڷ���
	if (XOR(left, enemyPosition.x < this->position.x)) {
		left = !left;
	}
}

void Character::updateCollisionWithPlatform(std::vector<Platform> platforms) {
	if (platforms.empty() || velocity.y < 0) return;
	bool onBoard = false;
	// ��������platform���ж��Ƿ�������
	for (const auto& platform : platforms) {
		sf::Vector2f platformStart = platform.startPosition;
		float platformWidth = platform.width;

		// ����Ƿ�վ��ƽ̨��
		if (position.y >= platformStart.y &&  // λ��ƽ̨�߶�
			position.y <= platformStart.y + TOLERANCE && // ����С��Χ���
			position.x >= platformStart.x && // ��ƽ̨��Χ��
			position.x <= platformStart.x + platformWidth) {
			onBoard = true;

			position.y = platformStart.y;  // վ������
			inAir = false;
			if (currentState != CharacterState::Running) {
				currentState = CharacterState::Stand;  // run��stand����Ҫplatform
			}
			velocity.y = 0.f;  // �����ֱ�ٶ�
			jumpTimes = 0;  // ������Ծ����
			
			break;
		}
	}
	if (!onBoard && (currentState == CharacterState::Stand || currentState == CharacterState::Running)) {
		currentState = CharacterState::Jumping;
		currentFrame = 0;
	}
}

void separate(Character* p1, Character* p2) {
	// Ĭ���Ѿ��غ�
	float r = std::fabs(p1->position.x - p2->position.x);
	bool left = p1->position.x < p2->position.x; // p1����߾ͻ�ø��ļ��ٶ�
	float acceleration = REPULSION / r;
	p1->gainVelocity({ acceleration * left ? -0.2f : 0.2f, 0 });
	p2->gainVelocity({ acceleration * left ? 0.2f : -0.2f, 0 });
}

void Character::updateCollisionWithEnemy(Character* enemy) {
	// �زĳߴ粻һ�������Ϊ���Ա����ظ����㣬���ڸ��¾���ʱ��Ҫ���жϣ�Ŀǰ֡��������ɲ��Ż�
	sf::FloatRect playerRect = this->sprite.getLocalBounds();
	sf::FloatRect enemyRect = enemy->sprite.getLocalBounds();
	playerRect.left = this->position.x - playerRect.width / 2.f;
	playerRect.top = this->position.y - playerRect.height / 2.f;
	enemyRect.left = enemy->position.x - enemyRect.width / 2.f;
	enemyRect.top = enemy->position.y - enemyRect.height / 2.f;
	// ǰ�᣺��������ȫ�غ�==>�غϵ����һ�߼���
	// �ƺ�ԭ��Ϸ�������������������ٶȱ仯��һ�£��еļ��룬�еĸ���
	// ���ﶼ����Ϊһ������������������ﵲ�������ٶȼ���
	if(!playerRect.intersects(enemyRect)) return;
	if (std::fabs(this->position.y - enemy->position.y) < TOLERANCE && this->velocity.x != 0.f) { // ͬ�߶ȣ�ˮƽ��ײ
		this->velocity.x /= 4.f;
		enemy->gainVelocity({this->velocity.x, 0.f});
	}
	separate(this, enemy);
}

void Character::gainVelocity(sf::Vector2f acceleration) {
	this->velocity += acceleration;
}



void Character::handleMove() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
		//return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveRight();
		//return;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = 0;  // ֹͣˮƽ�ƶ�
		if (currentState == CharacterState::Running) {
			currentState = CharacterState::Stand;
			currentFrame = 0;
		}
		//return;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // S�����������䡢�չ�3������3��Զ��3
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			down();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			// �չ�3
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			// ����3
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			// Զ��3
		}
		else {
			// ����
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

