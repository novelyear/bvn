#include "NarutoS.h"
#include "Constants.h"
#include "Character.h"


void NarutoS::handleMove() {
	// һ������
	if (currentState == CharacterState::Flash ||
		currentState == CharacterState::Hit ||
		currentState == CharacterState::Kick) {
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // ���
		if (jumpTimes > 1 || chakra <= CHAKRA_L) { //֮�󲹳�chakra�������Ƴ�̴�����ͬʱ����ֻ�ܳ��һ��
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
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				sj();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			// ����3
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				si();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				su();
			}
		}
		else { // ������S
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				s();
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) { // û��S ��K ����Ծ
		jump();
	}
	else if (currentState == CharacterState::S) { // û��S�����ڷ����������ɿ�S
		s_release(); // ����return���ɱ����
	}

	// Wϵ��
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				wj();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				wi();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				wu();
		}
	}
	else { // û��W
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				u();
			else if (jumpTimes <= 2 &&
				(currentState == CharacterState::Jumping ||
					currentState == CharacterState::Fall)) {
				ku();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				i();
		}
	}


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::J) &&
		(currentState == CharacterState::J1 ||
			currentState == CharacterState::J2 ||
			currentState == CharacterState::Stand ||
			currentState == CharacterState::Running ||
			currentState == CharacterState::Landed ||
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
			currentState == CharacterState::Landed ||
			currentState == CharacterState::J1 ||
			currentState == CharacterState::J2) { // �����ڵ���
			switch (attackStage) {
			case 0:
				j1(); // һ��J
				printf("J1\n");
				break;
			case 1:
				if (currentFrame > 6) { // �������������ÿ�����ﶨ��������ƣ���11��ֻ�������������ͬ��
					j2(); // ����J, ����11��ͼƬ����ܰ����������
					printf("J2\n");
				}
				break;
			case 2:
				if (currentFrame > 6) {// ���Σ��ȶ��β���6�Ų��ܰ�
					printf("J3\n");
					j3();
				}
				break;
			case 3:
				if (currentFrame > 10) { // �ĶΣ������β���10�Ų��ܴ���
					printf("J4\n");
					j4();
				}
			}
		}
	}

	// AD����
	if (
		currentState != CharacterState::Stand &&
		currentState != CharacterState::Running &&
		currentState != CharacterState::Landed &&
		currentState != CharacterState::Jumping &&
		currentState != CharacterState::Fall
		)
		return;

	// AD ���������Σ��ź���
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
	}

}