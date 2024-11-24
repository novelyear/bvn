#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"

void Character::update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) {
	//updateCollisionWithEnemy(enemy);
	updateCollisionWithPlatform(platforms);
	updatePosition(view);
	updateDirection(enemy->position);
	updateSprite(deltaTime);
}

void Character::updatePosition(sf::View view) {
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	// ��ȡ��ͼ�ĵ�ǰ�߽�
	float left = center.x - size.x / 2.f;
	float right = center.x + size.x / 2.f;


	position.x += velocity.x;
	if (currentState == CharacterState::Running ||
		currentState == CharacterState::Jumping ||
		currentState == CharacterState::Fall ||
		currentState == CharacterState::Stand)
	{
		velocity.x = 0;
	}
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
	// ���׻���
	if (position.y >= CHARACTER_BOTTOM) {
		position.y = CHARACTER_BOTTOM;  // ����λ��
		inAir = false;
		//if (currentState != CharacterState::Running) {
		//	currentState = CharacterState::Stand;  // run��stand����Ҫplatform
		//}
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
			if (currentState == CharacterState::Jumping || // ע��������Ķ��׻��Ʊ���һ��
				currentState == CharacterState::Fall) {
				currentState = CharacterState::Stand;
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
	if (currentState == CharacterState::Flash || enemy->currentState == CharacterState::Flash) {
		return;
	}
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
	if (!playerRect.intersects(enemyRect)) return;
	if (std::fabs(this->position.y - enemy->position.y) < TOLERANCE && this->velocity.x != 0.f) { // ͬ�߶ȣ�ˮƽ��ײ
		this->velocity.x /= 4.f;
		enemy->gainVelocity({ this->velocity.x, 0.f });
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
			break;
		case CharacterState::Fall:
			sprite.setTexture(textures[fall.first + currentFrame]);
			sprite.setOrigin(origins[fall.first + currentFrame]);
			if (currentFrame + fall.first < fall.second) currentFrame++;
			break;
		case CharacterState::J1:
			sprite.setTexture(textures[J1.first + currentFrame]);
			sprite.setOrigin(origins[J1.first + currentFrame]);
			currentFrame++;
			if (currentFrame + J1.first > J1.second) {
				if (attackStage > 1) {
					currentState = CharacterState::J2;
					currentFrame = 0;
				}
				else {
					currentState = CharacterState::Stand;
					currentFrame = 0;
					attackStage = 0;
				}
			}
			break;
		case CharacterState::J2:
			sprite.setTexture(textures[J2.first + currentFrame]);
			sprite.setOrigin(origins[J2.first + currentFrame]);
			currentFrame++;
			if (currentFrame + J2.first > J2.second) {
				if (attackStage > 2) {
					currentState = CharacterState::J3;
					currentFrame = 0;
				}
				else {
					currentState = CharacterState::Stand;
					currentFrame = 0;
					attackStage = 0;
				}
			}
			break;
		case CharacterState::J3:
			sprite.setTexture(textures[J3.first + currentFrame]);
			sprite.setOrigin(origins[J3.first + currentFrame]);
			currentFrame++;
			if (currentFrame + J3.first > J3.second) {
				attackStage = 0;
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::KJ:
			sprite.setTexture(textures[KJ.first + currentFrame]);
			sprite.setOrigin(origins[KJ.first + currentFrame]);
			currentFrame++;
			if (currentFrame + KJ.first > KJ.second) {
				currentState = CharacterState::Fall;
				currentFrame = 0;
			}
			break;
		case CharacterState::SJ:
			sprite.setTexture(textures[SJ.first + currentFrame]);
			sprite.setOrigin(origins[SJ.first + currentFrame]);
			currentFrame++;
			if (currentFrame + SJ.first > SJ.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;
		case CharacterState::SU:
			sprite.setTexture(textures[SU.first + currentFrame]);
			sprite.setOrigin(origins[SU.first + currentFrame]);
			currentFrame++;
			if (currentFrame + SU.first > SU.second) {
				currentState = CharacterState::Stand;
				currentFrame = 0;
			}
			break;

		default:
			break;
		}
		elapsedTime = 0.f;
		// �����������Ϊ��ǰ�������������
		sf::Vector2u textureSize = sprite.getTexture()->getSize(); // ��ȡ����ߴ�
		sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
		if (left)
			sprite.setScale(-1.f, 1.f); // ˮƽ���񣬴�ֱ���ֲ���
		else {
			sprite.setScale(1.f, 1.f);
		}
	}
	sprite.setPosition(position);
}
