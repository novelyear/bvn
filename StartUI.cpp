#include "Game.h"

StartUI::StartUI(sf::RenderWindow& win) : window(win) {
    loadResources(
        "D:\\D1\\code\\bvn\\access\\others\\start_textures_atlas.png",
        "D:\\D1\\code\\bvn\\access\\others\\start_anchors.txt",
        "D:\\D1\\code\\bvn\\access\\others\\button\\button.png",
        "D:\\D1\\code\\bvn\\access\\others\\button\\button_hover.png",
        "D:\\D1\\code\\bvn\\access\\others\\button\\button_pressed.png"
    );
}

void StartUI::loadResources(const std::string& textureFile, const std::string& anchorsFile,
	const std::string& buttonFile1, const std::string& buttonFile2, const std::string& buttonFile3) {
    // 加载纹理
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load texture file: " << textureFile << std::endl;
        return;
    }
    sprite.setTexture(texture);

    // 加载动画帧锚框
    std::ifstream anchorInput(anchorsFile);
    if (!anchorInput.is_open()) {
        std::cerr << "Failed to open rects file: " << anchorsFile << std::endl;
        return;
    }

    int x1, y1, width, height, index = 1;
    char delimiter;
    anchors.resize(91);
    while (anchorInput >> index >> delimiter >> delimiter >> x1 >> delimiter >> y1 >> delimiter >> width >> delimiter >> height >> delimiter) {
        if (index >= anchors.size()) {
            anchors.resize(index + 1);
        }
        anchors[index] = sf::IntRect(x1, y1, width, height);
    }
    anchorInput.close();

    // 加载按钮纹理
    buttonTextures[0].loadFromFile(buttonFile1);
    buttonTextures[1].loadFromFile(buttonFile2);
    buttonTextures[2].loadFromFile(buttonFile3);

    // 初始化按钮
    startButton.setSize(sf::Vector2f(200, 50));
    startButton.setTexture(&buttonTextures[0]); // 默认状态
    startButton.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 25);
}

bool StartUI::update(float deltaTime) {
    // 动画轮播
    if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame++;
        int limit = mouseClicked ? 89 : 65;
        if (currentFrame >= limit) currentFrame -= 15;
        sprite.setTextureRect(anchors[currentFrame]);
        frameClock.restart();
    }

    // 检测鼠标点击
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mouseClicked = true;
    }

    // 按钮状态更新
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = startButton.getGlobalBounds();

    if (buttonBounds.contains(mousePos.x, mousePos.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            startButton.setTexture(&buttonTextures[2]); // 按下状态
        } else {
            startButton.setTexture(&buttonTextures[1]); // hover状态
        }
    } else {
        startButton.setTexture(&buttonTextures[0]); // 默认状态
    }

    // 检测按钮点击完成
    if (mouseClicked && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (buttonBounds.contains((float)mousePos.x, (float)mousePos.y)) {
            // 点击完成，切换到角色选择状态
            mouseClicked = false;
            // 触发状态变更逻辑
            return true;
        }
    }
    return false;
}

void StartUI::render() {
    window.clear();
    sprite.setScale(2.f, 2.f);
    window.draw(sprite);
    if (mouseClicked) {
        window.draw(startButton);
    }
    window.display();
}
