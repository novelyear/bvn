#include "Player.h"

void Player::handleInput(){
	// ���ݰ��������ƶ�
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveRight();
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		velocity.x = 0;  // ֹͣˮƽ�ƶ�
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		jump();
	}
}
void Player::useSkill(){

}
