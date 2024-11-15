#include "Game.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

Game::Game(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title), player(), map() {
    // 初始化人物坐标啥的啊
    player.position.x = 100.f;
    player.position.y = 400.f;
    player.velocity = { 0, 0 };
    player.inAir = true;
    enemy.position.x = 0;
    enemy.position.y = 0;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}



void Game::processEvents() {
    player.handleInput();
    sf::Event event;
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
                std::cout << "mouse x:" << event.mouseButton.x << std::endl;
                std::cout << "mouse y:" << event.mouseButton.y << std::endl;
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Right)
                    std::cout << "right button Released" << std::endl;
                else if (event.mouseButton.button == sf::Mouse::Left)
                    std::cout << "left button Released" << std::endl;
                else if (event.mouseButton.button == sf::Mouse::Middle)
                    std::cout << "middle button Released" << std::endl;
                std::cout << "mouse x:" << event.mouseButton.x << std::endl;
                std::cout << "mouse y:" << event.mouseButton.y << std::endl;
                break;
            case sf::Event::MouseMoved:
            default:
                break;
        }
        // ==================
    }
}

void Game::update() {
    // 更新游戏状态：玩家位置、视窗位置
    player.update();

    view.reset(getView(player.position, enemy.position));

    map.checkCollision(player);
}

void Game::render() {
    window.clear();

    // 渲染背景
    map.render(window, view);

    // 渲染玩家
    player.render(window);

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
    height = width * 0.75;
    return sf::FloatRect(centerX, centerY, width, height);
}