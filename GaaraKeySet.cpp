#include "Gaara.h"

void Gaara::handleMove() {
	// 一级屏蔽
	if (currentState == CharacterState::Flash) {
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) { // 冲刺
		if (jumpTimes > 1) { //之后补充chakra机制限制冲刺次数，同时空中只能冲刺一次
			return;
		}
		flash();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // S：防御、下落、普攻3、大招3、远攻3
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			down();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::S)
			{
				sj();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			// 大招3
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::S)
			{
				su();
			}
		}
		else { // 单独的S
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::S)
			{
				s();
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) { // 没按S 有K 则跳跃
		jump();
	}
	else if (currentState == CharacterState::S) { // 没按S，但在防御，表明松开S
		s_release(); // 不加return，可被打断
	}

	// W系列
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			wj();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			wi();
		}
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
		) // 单独J
	{
		if (jumpTimes <= 2 &&
			(currentState == CharacterState::Jumping ||
				currentState == CharacterState::Fall)
			) { // 空中J
			kj();
		}
		else if (currentState == CharacterState::Stand ||
			currentState == CharacterState::Running ||
			currentState == CharacterState::J1 ||
			currentState == CharacterState::J2) { // 限制在地面
			switch (attackStage) {
			case 0:
				j1(); // 一段J
				printf("J1\n");
				break;
			case 1:
				if (currentFrame > 4) { // 后续加了人物就每个人物定制这个限制，“4”只针对我爱罗，下面同理
					j2(); // 二段J, 播放4张图片后才能按，否则忽略
					printf("J2\n");
				}
				break;
			case 2:
				if (currentFrame > 8) {// 三段，等二段播了10张才能按
					printf("J3\n");
					j3();
				}

			}
		}
	}



	// ADK屏蔽
	if (
		currentState != CharacterState::Stand &&
		currentState != CharacterState::Running &&
		currentState != CharacterState::Jumping &&
		currentState != CharacterState::Fall
		)
		return;

	// ADK 经常被屏蔽，放后面
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveLeft();
		//return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
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

}