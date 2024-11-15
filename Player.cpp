#include "Player.h"

Player::Player() {
	left = true;
}

void Player::handleMove() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveRight();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = 0;  // ֹͣˮƽ�ƶ�
	}
}

void Player::handleInput(sf::Event event){
	if (event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::K)
			jump();
	}
}
void Player::useSkill(){

}
