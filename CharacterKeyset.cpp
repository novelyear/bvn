#include "Character.h"
#include <bits/stdc++.h>
#include "Constants.h"


void Character::handleMove() {
	// һ������
	if (currentState == CharacterState::Flash) {
		return;
	}



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // ���
		if (jumpTimes > 1) { //֮�󲹳�chakra�������Ƴ�̴�����ͬʱ����ֻ�ܳ��һ��
			return;
		}
		flash();
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // S�����������䡢�չ�3������3��Զ��3
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			down();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running) {
				sj();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			// ����3
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running) {
				su();
			}
		}
		else { // ������S
			s();
			return; // ����״̬����ADK��L
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) { // û��S ��K ����Ծ
		jump();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::J) &&
			(currentState == CharacterState::J1 ||
			 currentState == CharacterState::J2 ||
			 currentState == CharacterState::Stand ||
			 currentState == CharacterState::Running || 
			 currentState == CharacterState::Jumping || 
			 currentState == CharacterState::Fall)
		) // ����J
	{
		if (jumpTimes <= 2 && 
			(currentState == CharacterState::Jumping ||
			currentState == CharacterState::Fall)
			) { // ����J
			kj();
		}
		else if (currentState == CharacterState::Stand ||
			     currentState == CharacterState::Running ||
				 currentState == CharacterState::J1 || 
				 currentState == CharacterState::J2) { // �����ڵ���
			switch (attackStage) { 
				case 0:
					j1(); // һ��J
					printf("J1\n");
					break;
				case 1:
					if (currentFrame > 4) { // �������������ÿ�����ﶨ��������ƣ���4��ֻ����Ұ��ޣ�����ͬ��
						j2(); // ����J, ����4��ͼƬ����ܰ����������
						printf("J2\n");
					}
					break;
				case 2:
					if (currentFrame > 8) {// ���Σ��ȶ��β���10�Ų��ܰ�
						printf("J3\n");
						j3();
					}

			}
		}
	}



	// ADK����
	if (
		currentState != CharacterState::Stand &&
		currentState != CharacterState::Running &&
		currentState != CharacterState::Jumping &&
		currentState != CharacterState::Fall
		) 
		return;

	// ADK ���������Σ��ź���
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
		//return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
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
}

void Character::handleInput(sf::Event event) {
	switch (currentState) {
		case CharacterState::Stand:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				moveLeft();
				//return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				moveRight();
				//return;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // ���
				if (jumpTimes > 1) { //֮�󲹳�chakra�������Ƴ�̴�����ͬʱ����ֻ�ܳ��һ��
					return;
				}
				flash();
				return;
			}
			break;
		case CharacterState::Running:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				moveLeft();
				//return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				moveRight();
				//return;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velocity.x = 0;  // ֹͣˮƽ�ƶ�
				currentState = CharacterState::Stand;
				currentFrame = 0;
				//return;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // ���
				if (jumpTimes > 1) { //֮�󲹳�chakra�������Ƴ�̴�����ͬʱ����ֻ�ܳ��һ��
					return;
				}
				flash();
				return;
			}
			break;
		case CharacterState::Jumping:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				moveLeft();
				//return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				moveRight();
				//return;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velocity.x = 0;  // ֹͣˮƽ�ƶ�
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // ���
				if (jumpTimes > 1) { //֮�󲹳�chakra�������Ƴ�̴�����ͬʱ����ֻ�ܳ��һ��
					return;
				}
				flash();
				return;
			}
		case CharacterState::Fall:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				moveLeft();
				//return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				moveRight();
				//return;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velocity.x = 0;  // ֹͣˮƽ�ƶ�
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // ���
				if (jumpTimes > 1) { //֮�󲹳�chakra�������Ƴ�̴�����ͬʱ����ֻ�ܳ��һ��
					return;
				}
				flash();
				return;
			}
		case CharacterState::Flash:
			break;
		case CharacterState::J1:

		case CharacterState::J2:

		case CharacterState::J3:

		default:
			break;
	}
}