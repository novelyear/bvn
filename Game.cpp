#include "Game.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.h"
#include "Factories.h"
Game::Game(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title) {}

void Game::selectCharacter() { // 后续加上选人逻辑
    player = CharacterFactory::createCharacter(CharacterType::Gaara, false);
    enemy = CharacterFactory::createCharacter(CharacterType::Gaara, true);

    enemyAI = std::make_unique<Controller>(enemy.get(), player.get());
}

void Game::selectMap() {
    map = MapFactory::createMap(MapType::MR);
}

void Game::run() {
    sf::Clock clock;  // 创建时钟对象，记录时间
    selectCharacter();
    selectMap();
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();  // 重置时钟并获取时间差
        //float fps = 1.f / deltaTime.asSeconds();  // 计算帧率
        //// 输出当前帧率到控制台
        //std::cout << "FPS: " << fps << std::endl;

        processEvents();
        update(deltaTime.asSeconds());
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    // 真人控制
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
            case sf::Event::KeyPressed:
                std::cout << event.key.code << std::endl;
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                    std::cout << "right button pressed" << std::endl;
                else if (event.mouseButton.button == sf::Mouse::Left)
                    std::cout << "left button pressed" << std::endl;
                std::cout << window.mapPixelToCoords({ event.mouseButton.x , event.mouseButton.y }).x << " " << window.mapPixelToCoords({ event.mouseButton.x , event.mouseButton.y }).y;
                std::cout << std::endl;
                break;
            default:
                break;
        }
        // ================== 
        //player->handleInput(event);
    }

    // 拟人控制
    enemyAI->process(map.get());
}

void Game::update(float deltaTime) {
    player->update(deltaTime, view, enemy.get(), map->platforms);
    enemy->update(deltaTime, view, player.get(), map->platforms);

    // 更新敌人状态：敌人位置，
    view.reset(getView(player->position, enemy->position));
}

void Game::render() {
    window.clear();
    map->render(window, view);
    // 渲染玩家
    player->render(window);
    // 渲染敌人
    enemy->render(window);
    enemy->effects->render(window);// 后渲染特效，遮住人物
    player->effects->render(window);
    window.setView(view);
    window.display();
}

sf::FloatRect Game::getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition) {
    // 以角色连线中点为中心，四周间距100.f
    float lowY = std::min(playerPosition.y, enemyPosition.y) - 80.f;
    float highY = std::max(playerPosition.y, enemyPosition.y);
    float centerX = (playerPosition.x - enemyPosition.x) / 2 + enemyPosition.x;
    float centerY = (highY - lowY) / 2 + lowY;
    float width, height;
    float disX = fabs(playerPosition.x - enemyPosition.x) + PUSH_MARGIN * 2.f;
    float disY = highY - lowY + PUSH_MARGIN * 1.5f;
    // 获取连线的外接矩形宽
    disX = std::max(disX, disY / 0.75f);
    // 控制视图缩放比
    width = std::max(std::min(disX, maximumViewWidth), minimumViewWidth);
    height = width * 0.75f;
    // 限制视图
    float Left = centerX - width / 2;
    float Top = centerY - height / 2;
    if (Left < 0.f) Left = 0.f;
    if (Left + width > RIGHT_BORDER) Left = RIGHT_BORDER - width;
    if (Top + height > GROUND) Top = GROUND - height;
    return sf::FloatRect(Left, Top, width, height);
}
// 仅以自己为视图中心，锁定镜头缩放比
sf::FloatRect Game::testView(sf::Vector2f playerPosition) {
    float Left = player->position.x - minimumViewWidth / 2;
    float Top = player->position.y - minimumViewWidth * 0.75f / 2;
    // 限制视窗底部在地面上，左部不超过左边界，右部不超过有边界
    if (Left < 0.f) Left = 0.f;
    if (Left + minimumViewWidth > RIGHT_BORDER) Left = RIGHT_BORDER - minimumViewWidth;

    if (Top + minimumViewWidth * 0.75f > GROUND) Top = GROUND - minimumViewWidth * 0.75f;
    return sf::FloatRect(Left, Top, minimumViewWidth, minimumViewWidth * 0.75f);
}