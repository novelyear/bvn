#include "Player.h"

void Player::handleInput(){
	// 根据按键持续移动
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveRight();
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		velocity.x = 0;  // 停止水平移动
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		jump();
	}
}
void Player::useSkill(){

}
