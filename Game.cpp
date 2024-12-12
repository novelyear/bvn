#include "Game.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.h"
#include "Factories.h"
Game::Game(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title) {
    state = GameState::Init;
    startUI = std::make_unique<StartUI>(window);
    if (!blackPng.loadFromFile("./access/black.png")) {
        printf("black error\n");
    }
    blackBG.setTexture(blackPng);
}
// 选人界面加载
void Game::selectCharacter() {
    // 加载角色头像纹理
    characterTextures[0].loadFromFile("D:\\D1\\code\\bvn\\access\\avater\\gaara.png");
    characterTextures[1].loadFromFile("D:\\D1\\code\\bvn\\access\\avater\\naruto_hermit.png");

    // 创建对应的Sprite
    for (int i = 0; i < characterTypes.size(); ++i) {
        sf::Sprite sprite;
        sprite.setTexture(characterTextures[i]);
        sprite.setPosition(200.f + i * 150.f, 300.f); // 假设每个角色间隔150像素
        characterSprites.push_back(sprite);
    }
}
// 选人界面处理输入和渲染
void Game::handleCharacterSelection() {
    // 渲染选人界面
    window.clear(sf::Color::Black);

    sf::Font font;
    font.loadFromFile("./access/others/HanYiXiangSu-11px-U/retro-pixel-arcade.ttf");
    sf::Text instruction("Press Left/Right to Choose, Enter to Confirm", font, 20);
    instruction.setPosition(200, 200);
    window.draw(instruction);

    // 绘制角色选项
    for (size_t i = 0; i < characterSprites.size(); ++i) {
        if (i == selectedCharacterIndex) {
            sf::RectangleShape highlightBox(sf::Vector2f(128, 128)); // 假设头像是128x128
            highlightBox.setPosition(characterSprites[i].getPosition());
            highlightBox.setFillColor(sf::Color(0, 0, 0, 0));
            highlightBox.setOutlineColor(sf::Color::Yellow);
            highlightBox.setOutlineThickness(3);
            window.draw(highlightBox);
        }
        window.draw(characterSprites[i]);
    }

    window.display();

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: // 处理窗口关闭
            window.close();
            break;

        case sf::Event::KeyPressed: // 按键按下时处理逻辑
            if (event.key.code == sf::Keyboard::Right) {
                selectedCharacterIndex = (selectedCharacterIndex + 1) % characterSprites.size();
            }
            else if (event.key.code == sf::Keyboard::Left) {
                selectedCharacterIndex = (selectedCharacterIndex - 1 + characterSprites.size()) % (int)characterSprites.size();
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                player = CharacterFactory::createCharacter(characterTypes[selectedCharacterIndex], false);
                enemy = CharacterFactory::createCharacter(characterTypes[(selectedCharacterIndex + 1) % characterSprites.size()], true);
                enemyAI = std::make_unique<Controller>(enemy.get(), player.get());
                state = GameState::Playing; // 切换到游戏状态
            }
            break;

        default:
            break;
        }
    }
}



// 选地图
void Game::selectMap() {
    map = MapFactory::createMap(MapType::MR);
}

void Game::gameover() {
    state = GameState::Over;
    // 绘制最后一击特效

    // 给被击倒方特写

    // 给胜利方特写，播放胜利方animation_win

    // 屏幕结算
    sf::Font font;
    if (!font.loadFromFile("./access/others/HanYiXiangSu-11px-U/retro-pixel-arcade.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50); // 设置字体大小
    gameOverText.setFillColor(sf::Color::Red); // 设置字体颜色
    gameOverText.setStyle(sf::Text::Bold); // 设置字体样式

    if (player->health < 0) {
        gameOverText.setString("You Lose!");
    }
    else {
        gameOverText.setString("You Win!");
    }

    // 获取窗口大小
    sf::Vector2f windowSize = view.getSize();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();
    sf::Vector2f viewTopLeft = { center.x - size.x / 2, center.y - size.y / 2 };
    // 计算文字宽高
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    // 将文字放在窗口中心
    gameOverText.setPosition(viewTopLeft.x + static_cast<float>(windowSize.x) / 2.0f,
        viewTopLeft.y + static_cast<float>(windowSize.y) / 2.0f);

    // 等待鼠标点击的循环
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                return; // 鼠标点击时退出
            }
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        // 渲染文字
        window.draw(gameOverText);
        window.display();
    }
}

// 主
void Game::run() {
    sf::Clock clock;  // 创建时钟对象，记录时间
    
    selectCharacter();
    selectMap();

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        switch (state) {
        case GameState::Init:
            if (startUI->update(deltaTime.asSeconds())) state = GameState::SelectCharacter;
            startUI->render();
            break;
        case GameState::SelectCharacter:
            handleCharacterSelection();
            break;
        case GameState::Playing:
            processEvents();
            update(deltaTime.asSeconds());
            render();
            break;
        case GameState::Over:
            /*state = GameState::Init;
            currentViewLeft = 0.f;
            currentViewTop = 0.f;
            currentViewWidth = minimumViewWidth;
            currentViewHeight = minimumViewWidth * 0.75f;
            view.reset(sf::FloatRect(0, 0, 1000.f, 1000.f));*/
            window.close();
            break;
        }
    }
    //float fps = 1.f / deltaTime.asSeconds();  // 计算帧率
    //// 输出当前帧率到控制台
    //std::cout << "FPS: " << fps << std::endl;
}
// 战斗键控
void Game::processEvents() {
    sf::Event event;
    // 真人控制
    player->handleMove();
    enemy->handleMove();
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
                std::cout << event.mouseButton.x << "  " << event.mouseButton.y << std::endl;
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
    //enemyAI->process(map.get());
}


void Game::triggerShake(float intensity, float duration) {
    cameraShake.startShake(intensity, duration);
}

void Game::handleCharacterEvents(Character* character) {
    while (character->hasEvents()) {
        EventType event = character->popEvent();
        switch (event) {
        case EventType::SkillHit:
            triggerShake(AMPLITUDE, SHAKE_KICK); // 技能命中震屏
            break;
        case EventType::FallImpact:
            triggerShake(AMPLITUDE, SHAKE_KICK); // 落地震屏
            break;
        }
    }
}

void Game::updateView(float deltaTime) {
    // 更新震屏偏移
    sf::Vector2f shakeOffset = cameraShake.update();

    // 将偏移应用到视图
    sf::Vector2f viewCenter = { currentViewLeft + currentViewWidth / 2,
                                currentViewTop + currentViewHeight / 2 };
    view.setCenter(viewCenter + shakeOffset);
}

// 战斗更新
void Game::update(float deltaTime) {
    pause.update(deltaTime, player->pauseEventQueue);
    pause.update(deltaTime, enemy->pauseEventQueue);
    if (!pause.isPausedFor(enemy.get()))
        enemy->update(deltaTime, view, player.get(), map->platforms);
    if (!pause.isPausedFor(player.get()))
        player->update(deltaTime, view, enemy.get(), map->platforms);

    // 处理角色事件
    handleCharacterEvents(player.get());
    handleCharacterEvents(enemy.get());

    view.reset(getView(player->position, enemy->position, deltaTime));
    updateView(deltaTime);
    if (player->health < 0 || enemy->health < 0) {
        gameover();
    }
}
// 战斗渲染
void Game::render() {
    window.clear();
    if (pause.isPausedFor(player.get()) ^ pause.isPausedFor(enemy.get())) {
        blackBG.setPosition(window.mapPixelToCoords({ 0, 0 }));
        // 获取窗口的视图大小（即可视区域的大小）
        sf::Vector2f viewSize = view.getSize();
        blackBG.setScale(
            static_cast<float>(viewSize.x) / blackBG.getLocalBounds().width,
            static_cast<float>(viewSize.y) / blackBG.getLocalBounds().height
        );
        window.draw(blackBG);
    }
    else 
        map->render(window, view);
    
    // 渲染敌人
    enemy->render(window);
    // 渲染玩家
    player->render(window);
    enemy->effects->render(window);// 后渲染特效，遮住人物
    player->effects->render(window);

    enemy->cUI->render(window);
    player->cUI->render(window);
    window.setView(view);
    window.display();
}
// 双人焦点视图
sf::FloatRect Game::getView(sf::Vector2f playerPosition, sf::Vector2f enemyPosition, float deltaTime) {
    // 目标视图参数
    float lowY = std::min(playerPosition.y, enemyPosition.y) - 80.f;
    float highY = std::max(playerPosition.y, enemyPosition.y);
    float centerX = (playerPosition.x - enemyPosition.x) / 2 + enemyPosition.x;
    float centerY = (highY - lowY) / 2 + lowY;

    float disX = fabs(playerPosition.x - enemyPosition.x) + PUSH_MARGIN * 2.f;
    float disY = highY - lowY + PUSH_MARGIN * 1.5f;

    // 获取连线的外接矩形宽
    disX = std::max(disX, disY / 0.75f);

    // 控制视图缩放比
    float targetWidth = std::max(std::min(disX, maximumViewWidth), minimumViewWidth);
    float targetHeight = targetWidth * 0.75f;

    // 限制视图
    float targetLeft = centerX - targetWidth / 2;
    float targetTop = centerY - targetHeight / 2;

    if (targetLeft < 0.f) targetLeft = 0.f;
    if (targetLeft + targetWidth > RIGHT_BORDER) targetLeft = RIGHT_BORDER - targetWidth;
    if (targetTop + targetHeight > GROUND) targetTop = GROUND - targetHeight;

    // 平滑调整视图位置
    float smoothingFactor = 5.f; // 调整速度，值越大调整越快
    currentViewLeft += (targetLeft - currentViewLeft) * smoothingFactor * deltaTime;
    currentViewTop += (targetTop - currentViewTop) * smoothingFactor * deltaTime;
    currentViewWidth += (targetWidth - currentViewWidth) * smoothingFactor * deltaTime;
    currentViewHeight += (targetHeight - currentViewHeight) * smoothingFactor * deltaTime;

    return sf::FloatRect(currentViewLeft, currentViewTop, currentViewWidth, currentViewHeight);
}

// 单人焦点视图
sf::FloatRect Game::testView(sf::Vector2f playerPosition) {
    float Left = player->position.x - minimumViewWidth / 2;
    float Top = player->position.y - minimumViewWidth * 0.75f / 2;
    // 限制视窗底部在地面上，左部不超过左边界，右部不超过有边界
    if (Left < 0.f) Left = 0.f;
    if (Left + minimumViewWidth > RIGHT_BORDER) Left = RIGHT_BORDER - minimumViewWidth;

    if (Top + minimumViewWidth * 0.75f > GROUND) Top = GROUND - minimumViewWidth * 0.75f;
    return sf::FloatRect(Left, Top, minimumViewWidth, minimumViewWidth * 0.75f);
}