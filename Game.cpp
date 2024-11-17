#include "Game.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.h"
#include "CharacterFactory.h"

Game::Game(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title), map() {}

void Game::selectCharacter() { // ��������ѡ���߼�
    player = CharacterFactory::createCharacter(CharacterType::Gaara, false);
    enemy = CharacterFactory::createCharacter(CharacterType::Gaara, true);
}

void Game::run() {
    sf::Clock clock;  // ����ʱ�Ӷ��󣬼�¼ʱ��
    selectCharacter();
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();  // ����ʱ�Ӳ���ȡʱ���
        //float fps = 1.0f / deltaTime.asSeconds();  // ����֡��
        //// �����ǰ֡�ʵ�����̨
        //std::cout << "FPS: " << fps << std::endl;

        processEvents();
        update(deltaTime.asSeconds());
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    // ��������¼�
    player->handleMove();
    

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        // ==================
        switch (event.type) {
            case sf::Event::Closed:
                std::cout << "good byyyye" << std::endl;
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "height:" << event.size.height << std::endl;
                std::cout << "weight:" << event.size.width << std::endl;
                break;
            case sf::Event::LostFocus:
                std::cout << "hei! what are you doing!\n";
                break;
            case sf::Event::GainedFocus:
                std::cout << "ok.." << std::endl;
                break;
            case sf::Event::KeyPressed:
                std::cout << event.key.code << std::endl;
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128)
                    std::cout << "ASCII character typed :" << static_cast<char>(event.text.unicode) << std::endl;
                break;
            case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: Horizontal" << std::endl;
                else
                    std::cout << "while type: unknown" << std::endl;
                std::cout << "wheel delta:" << event.mouseWheelScroll.delta << std::endl;
                std::cout << "wheel x:" << event.mouseWheelScroll.x << std::endl;
                std::cout << "wheel y:" << event.mouseWheelScroll.y << std::endl;
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                    std::cout << "right button pressed" << std::endl;
                else if (event.mouseButton.button == sf::Mouse::Left)
                    std::cout << "left button pressed" << std::endl;
                else if (event.mouseButton.button == sf::Mouse::Middle)
                    std::cout << "middle button pressed" << std::endl;
         /*       std::cout << "mouse x:" << event.mouseButton.x << std::endl;
                std::cout << "mouse y:" << event.mouseButton.y << std::endl;*/
                std::cout << window.mapPixelToCoords({ event.mouseButton.x , event.mouseButton.y }).x << " " << window.mapPixelToCoords({ event.mouseButton.x , event.mouseButton.y }).y;
                std::cout << std::endl;
                break;
            case sf::Event::MouseMoved:
            default:
                break;
        }
        // ==================
        player->handleInput(event);
    }
}

void Game::update(float deltaTime) {
    // ������Ϸ״̬�����λ�á��Ӵ�λ��
    player->update(deltaTime);
    // ���µ���״̬������λ�ã�
    //view.reset(getView(player.position, enemy.position));
    view.reset(testView(player->position));

    //map.checkCollision(player);
}

void Game::render() {
    window.clear();

    // ��Ⱦ����
    map.render(window, view);

    // ��Ⱦ���
    player->render(window);
    // ��Ⱦ����
    enemy->render(window);

    window.setView(view);

    window.display();
}

sf::FloatRect Game::getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition) {
    float centerX = (playerPosition.x - enemyPosition.x) / 2 + enemyPosition.x;
    float centerY = (playerPosition.y - enemyPosition.y) / 2 + enemyPosition.y;
    float width, height;
    float disX = fabs(playerPosition.x - enemyPosition.x);
    float disY = fabs(playerPosition.y - enemyPosition.y);
    width = std::max(std::min(disX, maximumViewWidth), minimumViewWidth);
    height = width * 0.75f;
    return sf::FloatRect(centerX, centerY, width, height);
}

sf::FloatRect Game::testView(sf::Vector2f playerPosition) {
    float Left = player->position.x - minimumViewWidth / 2;
    float Top = player->position.y - minimumViewWidth * 0.75f / 2;
    // �����Ӵ��ײ��ڵ����ϣ��󲿲�������߽磬�Ҳ��������б߽�
    if (Left < 0.f) Left = 0.f;
    if (Left + minimumViewWidth > RIGHT_BORDER) Left = RIGHT_BORDER - minimumViewWidth;

    if (Top + minimumViewWidth * 0.75f > GROUND) Top = GROUND - minimumViewWidth * 0.75f;
    return sf::FloatRect(Left, Top, minimumViewWidth, minimumViewWidth * 0.75f);
}