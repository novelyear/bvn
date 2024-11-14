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

        // ������ҵ������¼��������ƶ�����Ծ��
        player.handleInput(event);
    }
}

void Game::update() {
    // ������Ϸ״̬�����λ�á�������������
    float windowCenter = getCenter();
    map.update(windowCenter);
    player.update();
    map.checkCollision(player);
}

void Game::render() {
    window.clear();

    // ��Ⱦ����
    map.render(window);

    // ��Ⱦ���
    player.render(window);

    window.display();
}

float Game::getCenter() {
    // TODO ��������ֱ������
    float center = (player.position.x + enemy.position.x) / 2.0f;
    return center;
}