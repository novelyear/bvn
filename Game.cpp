#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title), player(), map() {}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // 处理玩家的输入事件，比如移动、跳跃等
        player.handleInput(event);
    }
}

void Game::update() {
    // 更新游戏状态：玩家位置、窗口缩放因子
    float windowCenter = getCenter();
    map.update(windowCenter);
    player.update();
    map.checkCollision(player);
}

void Game::render() {
    window.clear();

    // 渲染背景
    map.render(window);

    // 渲染玩家
    player.render(window);

    window.display();
}

float Game::getCenter() {
    // TODO 还得做垂直的中心
    float center = (player.position.x + enemy.position.x) / 2.0f;
    return center;
}