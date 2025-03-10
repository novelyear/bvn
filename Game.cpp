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
    loadAudios();
}

void Game::loadAudios() {
    gameAudio.loadMusic("bgm", "./access/sound/bgm.mp3");
    gameAudio.loadMusic("op", "./access/sound/op.mp3");
    gameAudio.loadSound("gaara_attack", "./access/sound/gaara_attack.mp3");
    gameAudio.loadSound("gaara_I", "./access/sound/gaara_I.mp3");
    gameAudio.loadSound("gaara_kick", "./access/sound/gaara_kick.mp3");
    gameAudio.loadSound("gaara_SI", "./access/sound/gaara_SI.mp3");
    gameAudio.loadSound("gaara_WI", "./access/sound/gaara_WI.mp3");
    gameAudio.loadSound("gaara_SI_Boom", "./access/sound/gaara_SI_Boom.mp3");
    gameAudio.loadSound("gaara_U", "./access/sound/gaara_U.mp3");
    gameAudio.loadSound("narutoS_I", "./access/sound/narutoS_I.mp3");
    gameAudio.loadSound("narutoS_KI", "./access/sound/narutoS_KI.mp3");
    gameAudio.loadSound("narutoS_SI1", "./access/sound/narutoS_SI1.mp3");
    gameAudio.loadSound("narutoS_SI2", "./access/sound/narutoS_SI2.mp3");
    gameAudio.loadSound("narutoS_SJ", "./access/sound/narutoS_SJ.mp3");
    gameAudio.loadSound("narutoS_SUU", "./access/sound/narutoS_SUU.mp3");
    gameAudio.loadSound("narutoS_U", "./access/sound/narutoS_U.mp3");
    gameAudio.loadSound("narutoS_WI", "./access/sound/narutoS_WI.mp3");
    gameAudio.loadSound("hit", "./access/sound/hit_s.mp3");
    gameAudio.loadSound("kick", "./access/sound/kick_s.mp3");
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
    static bool selectingFirstPlayer = true; // 标记当前是否在选择1P
    static size_t player1SelectionIndex = 0; // 记录1P选择的角色索引

    // 渲染选人界面
    window.clear(sf::Color::Black);

    sf::Font font;
    font.loadFromFile("./access/others/HanYiXiangSu-11px-U/retro-pixel-arcade.ttf");

    std::string instructionText = selectingFirstPlayer
        ? "Player 1: Press Left/Right to Choose, Enter to Confirm"
        : "Player 2: Press Left/Right to Choose, Enter to Confirm";

    sf::Text instruction(instructionText, font, 20);
    instruction.setPosition(200, 200);
    window.draw(instruction);

    // 绘制角色选项
    for (size_t i = 0; i < characterSprites.size(); ++i) {
        if (i == selectedCharacterIndex) {
            sf::RectangleShape highlightBox(sf::Vector2f(128, 128)); // 假设头像是128x128
            highlightBox.setPosition(characterSprites[i].getPosition());
            highlightBox.setFillColor(sf::Color(0, 0, 0, 0));
            highlightBox.setOutlineColor(selectingFirstPlayer ? sf::Color::Yellow : sf::Color::Blue);
            highlightBox.setOutlineThickness(3);
            window.draw(highlightBox);
        }
        window.draw(characterSprites[i]);
    }

    window.display();

    // 处理输入事件
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
                if (selectingFirstPlayer) {
                    // 确认1P选择
                    player1SelectionIndex = selectedCharacterIndex;
                    player = CharacterFactory::createCharacter(characterTypes[player1SelectionIndex], false);
                    selectingFirstPlayer = false; // 切换到2P选择阶段
                }
                else {
                    // 确认2P选择
                    size_t player2SelectionIndex = selectedCharacterIndex;
                    enemy = CharacterFactory::createCharacter(characterTypes[player2SelectionIndex], true);
                    enemyAI = std::make_unique<Controller>(enemy.get(), player.get());
                    gameAudio.stopMusic();
                    state = GameState::Playing; // 切换到游戏状态
                }
            }
            break;

        default:
            break;
        }
    }
}


void Game::selectMap() {
    // 初始化地图选项
    std::vector<sf::Sprite> mapSprites;  // 存储地图背景图片的精灵
    std::vector<MapType> mapTypes = { MapType::MR, MapType::VE };
    size_t selectedMapIndex = 0;

    // 加载背景图片
    sf::Texture mapTextureMR, mapTextureVE;
    if (!mapTextureMR.loadFromFile("./access/maps/louding.png") ||
        !mapTextureVE.loadFromFile("./access/maps/pubu.png")) {
        std::cerr << "Failed to load map preview images!" << std::endl;
        return;
    }

    // 配置地图精灵
    sf::Sprite mapSpriteMR(mapTextureMR);
    sf::Sprite mapSpriteVE(mapTextureVE);

    mapSpriteMR.setPosition(150, 200);  // 设置位置
    mapSpriteVE.setPosition(650, 200);

    mapSprites.push_back(mapSpriteMR);
    mapSprites.push_back(mapSpriteVE);

    // 字体和文本
    sf::Font font;
    if (!font.loadFromFile("./access/others/HanYiXiangSu-11px-U/retro-pixel-arcade.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text instruction("Use Left/Right to Select a Map, Enter to Confirm", font, 20);
    instruction.setPosition(200, 100);

    sf::RectangleShape highlightBox(sf::Vector2f(450, 240));
    highlightBox.setFillColor(sf::Color(0, 0, 0, 0));  // 透明填充
    highlightBox.setOutlineColor(sf::Color::Yellow);
    highlightBox.setOutlineThickness(3);

    // 循环处理选地图逻辑
    while (window.isOpen() && state == GameState::SelectMap) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Right) {
                    selectedMapIndex = (selectedMapIndex + 1) % mapSprites.size();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    selectedMapIndex = (selectedMapIndex - 1 + mapSprites.size()) % mapSprites.size();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    // 创建地图并进入选人界面
                    map = MapFactory::createMap(mapTypes[selectedMapIndex]);
                    state = GameState::SelectCharacter;
                }
                break;

            default:
                break;
            }
        }

        // 渲染选地图界面
        window.clear(sf::Color::Black);
        window.draw(instruction);

        for (size_t i = 0; i < mapSprites.size(); ++i) {
            window.draw(mapSprites[i]);
        }

        highlightBox.setPosition(mapSprites[selectedMapIndex].getPosition());
        window.draw(highlightBox);

        window.display();
    }
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
    gameOverText.setCharacterSize(25); // 设置字体大小
    gameOverText.setFillColor(sf::Color::Red); // 设置字体颜色
    gameOverText.setStyle(sf::Text::Regular); // 设置字体样式

    if (player->health < 0) {
        gameOverText.setString("2P win");
    }
    else {
        gameOverText.setString("1P win");
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
            gameAudio.playMusic("op", true);
            if (startUI->update(deltaTime.asSeconds())) state = GameState::SelectMap;
            startUI->render();
            break;
        case GameState::SelectMap:
            selectMap();
            break;
        case GameState::SelectCharacter:
            handleCharacterSelection();
            break;
        case GameState::Playing:
            gameAudio.playMusic("bgm", true);
            processEvents();
            update(deltaTime.asSeconds());
            render();
            break;
        case GameState::Over:
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
    while (!character->audioEventQueue.empty()) {
        std::string name = character->audioEventQueue.front();character->audioEventQueue.pop();
        gameAudio.playSound(name);
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
    enemy->defaultEffects->render(window);
    player->defaultEffects->render(window);
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
    if (targetLeft + targetWidth > Map::RIGHT_BORDER) targetLeft = Map::RIGHT_BORDER - targetWidth;
    if (targetTop + targetHeight > Map::GROUND) targetTop = Map::GROUND - targetHeight;

    // 平滑调整视图位置
    float smoothingFactor = 5.f; // 平滑速度
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
    if (Left + minimumViewWidth > Map::RIGHT_BORDER) Left = Map::RIGHT_BORDER - minimumViewWidth;

    if (Top + minimumViewWidth * 0.75f > Map::GROUND) Top = Map::GROUND - minimumViewWidth * 0.75f;
    return sf::FloatRect(Left, Top, minimumViewWidth, minimumViewWidth * 0.75f);
}