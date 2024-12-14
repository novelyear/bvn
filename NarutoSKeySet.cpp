#include "NarutoS.h"
#include "Constants.h"
#include "Character.h"
#include "keyMap.h"


void NarutoS::handleMove() {
	// 一级屏蔽s
	if (currentState == CharacterState::Flash ||
		currentState == CharacterState::Hit ||
		currentState == CharacterState::Kick) {
		return;
	}
	if (sf::Keyboard::isKeyPressed(key[real]["L"])) { // 冲刺
		if (jumpTimes > 1 || chakra <= CHAKRA_L) { //之后补充chakra机制限制冲刺次数，同时空中只能冲刺一次
			return;
		}
		flash();
		return;
	}

	if (sf::Keyboard::isKeyPressed(key[real]["S"])) { // S：防御、下落、普攻3、大招3、远攻3
		if (sf::Keyboard::isKeyPressed(key[real]["K"])) {
			down();
		}
		else if (sf::Keyboard::isKeyPressed(key[real]["J"])) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				sj();
			}
		}
		else if (sf::Keyboard::isKeyPressed(key[real]["I"])) {
			// 大招3
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				si();
			}
		}
		else if (sf::Keyboard::isKeyPressed(key[real]["U"])) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				su();
			}
			else if (currentState == CharacterState::SU && currentFrame > 10) { // SU打完才能触发suu
				suu();
			}
		}
		else { // 单独的S
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S)
			{
				s();
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(key[real]["K"])) { // 没按S 有K 则跳跃
		jump();
	}
	else if (currentState == CharacterState::S) { // 没按S，但在防御，表明松开S
		s_release(); // 不加return，可被打断
	}

	// W系列
	if (sf::Keyboard::isKeyPressed(key[real]["W"])) {
		if (sf::Keyboard::isKeyPressed(key[real]["J"])) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				wj();
		}
		else if (sf::Keyboard::isKeyPressed(key[real]["I"])) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				wi();
		}
		else if (sf::Keyboard::isKeyPressed(key[real]["U"])) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				wu();
			else if (currentState == CharacterState::WU && currentFrame > 24) { // WU24帧后才能触发WUU
				wuu();
			}
		}
	}
	else { // 没按W
		if (sf::Keyboard::isKeyPressed(key[real]["U"])) {
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
		else if (sf::Keyboard::isKeyPressed(key[real]["I"])) {
			if (currentState == CharacterState::Stand ||
				currentState == CharacterState::Running ||
				currentState == CharacterState::Landed ||
				currentState == CharacterState::S_Release)
				i();
			else if (currentState == CharacterState::Jumping ||
				currentState == CharacterState::Fall)
				ki();
		}
	}


	if (!sf::Keyboard::isKeyPressed(key[real]["S"]) &&
		!sf::Keyboard::isKeyPressed(key[real]["W"]) &&
		sf::Keyboard::isKeyPressed(key[real]["J"]) &&
		(currentState == CharacterState::J1 ||
			currentState == CharacterState::J2 ||
			currentState == CharacterState::Stand ||
			currentState == CharacterState::Running ||
			currentState == CharacterState::Landed ||
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
			currentState == CharacterState::Landed ||
			currentState == CharacterState::J1 ||
			currentState == CharacterState::J2) { // 限制在地面
			switch (attackStage) {
			case 0:
				j1(); // 一段J
				printf("J1\n");
				break;
			case 1:
				if (currentFrame > 3) { // 后续加了人物就每个人物定制这个限制
					j2(); // 二段J, 播放11张图片后才能按，否则忽略
					printf("J2\n");
				}
				break;
			case 2:
				if (currentFrame > 4) {// 三段，等二段播了4张才能按
					printf("J3\n");
					j3();
				}
				break;
			case 3:
				if (currentFrame > 6) { // 四段，等三段播了6张才能触发
					printf("J4\n");
					j4();
				}
			}
		}
	}

	// AD屏蔽
	if (
		currentState != CharacterState::Stand &&
		currentState != CharacterState::Running &&
		currentState != CharacterState::Landed &&
		currentState != CharacterState::Jumping &&
		currentState != CharacterState::Fall
		)
		return;

	// AD 经常被屏蔽，放后面
	if (sf::Keyboard::isKeyPressed(key[real]["A"])) {
		moveLeft();
		//return;
	}
	else if (sf::Keyboard::isKeyPressed(key[real]["D"])) {
		moveRight();
		//return;
	}
	if (!sf::Keyboard::isKeyPressed(key[real]["A"]) && !sf::Keyboard::isKeyPressed(key[real]["D"])) {
		velocity.x = 0;  // 停止水平移动
		if (currentState == CharacterState::Running) {
			currentState = CharacterState::Stand;
			currentFrame = 0;
		}
	}

}