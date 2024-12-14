#include "Map.h"
#include <bits/stdc++.h>

float Map::LEFT_BORDER = 0.0f;
float Map::RIGHT_BORDER = 0.0f;
float Map::GROUND = 0.0f;
float Map::CHARACTER_BOTTOM = 0.0f;

Map::Map() {}

Platform::Platform(sf::Vector2f startPosition, float width) {
    this->startPosition = startPosition;
    this->width = width;
}

MR::MR() : Map() {
    loadMap();
    loadPlatform();
    Map::LEFT_BORDER = 0.f;
    Map::RIGHT_BORDER = 800.f;
    Map::GROUND = 600.f;
    Map::CHARACTER_BOTTOM = 550.f;
}

void MR::render(sf::RenderWindow& window, sf::View& view) {
    if (!foregroundLayer.getTexture() || !backgroundLayer.getTexture()) {
        loadMap();
    }
    if (platforms.empty()) {
        loadPlatform();
    }
    backgroundLayer.setPosition(window.mapPixelToCoords({ 0, 0 }));

    // 获取窗口的视图大小（即可视区域的大小）
    sf::Vector2f viewSize = view.getSize();

    // 大背景左上角始终为视图的左上角
    backgroundLayer.setScale(
        static_cast<float>(viewSize.x) / backgroundLayer.getLocalBounds().width,
        static_cast<float>(viewSize.y) / backgroundLayer.getLocalBounds().height
    );
    foregroundLayer.setPosition({ 0, 0 });

    window.draw(backgroundLayer);
    window.draw(foregroundLayer);
}

void MR::loadMap() {
    // 加载远景和近景纹理
    if (!backgroundLayerTexture.loadFromFile("access\\bg2.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    else {
        backgroundLayer.setTexture(backgroundLayerTexture);
    }

    if (!foregroundLayerTexture.loadFromFile("access\\foreground.png")) {
        std::cerr << "Failed to load foreground texture!" << std::endl;
    }
    else {
        foregroundLayer.setTexture(foregroundLayerTexture);
    }
}

void MR::loadPlatform() {
    // 硬编码该地图上的平板
    // 0   45  80  75 160  175 x
    // 550 470 380 280 200 105 y
    // 800 715 637 635 470 435 长度
    platforms.push_back(Platform({ 0, 550 }, 800));
    platforms.push_back(Platform({ 45, 470 }, 715));
    platforms.push_back(Platform({ 80, 380 }, 637));
    platforms.push_back(Platform({ 75, 280 }, 635));
    platforms.push_back(Platform({ 160, 200 }, 470));
    platforms.push_back(Platform({ 175, 105 }, 435));
}

VE::VE() {
    loadMap();
    loadPlatform();
    Map::LEFT_BORDER = 0.f;
    Map::RIGHT_BORDER = 1000.f;
    Map::GROUND = 395.f;
    Map::CHARACTER_BOTTOM = 365.f;
}

void VE::loadMap() {
    // 加载远景和近景纹理
    if (!backgroundLayerTexture.loadFromFile("./access/pubu.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    else {
        backgroundLayer.setTexture(backgroundLayerTexture);
    }

    if (!foregroundLayerTexture.loadFromFile("./access/valley.png")) {
        std::cerr << "Failed to load foreground texture!" << std::endl;
    }
    else {
        foregroundLayer.setTexture(foregroundLayerTexture);
    }
}

void VE::loadPlatform() {
    // 硬编码该地图上的平板
    platforms.push_back(Platform({ 178, 62 }, 64)); // 斑头
    platforms.push_back(Platform({ 0, 158 }, 70));  // 斑背
    platforms.push_back(Platform({ 130, 145 }, 64));// 斑肩
    platforms.push_back(Platform({ 15, 293 }, 190));// 斑手
    platforms.push_back(Platform({ 0, 365 }, 1000)); // 地
    platforms.push_back(Platform({ 328, 274 }, 70));// 左柱
    platforms.push_back(Platform({ 465, 308 }, 70));// 中柱
    platforms.push_back(Platform({ 602, 264 }, 70));// 右柱
    platforms.push_back(Platform({ 768, 62 }, 64)); // 柱间头
    platforms.push_back(Platform({ 808, 145 }, 64));// 柱间肩
    platforms.push_back(Platform({ 877, 158 }, 70));// 柱间背
    platforms.push_back(Platform({ 797, 293 }, 190));// 柱间手
}

void VE::render(sf::RenderWindow& window, sf::View& view) {
    if (!foregroundLayer.getTexture() || !backgroundLayer.getTexture()) {
        loadMap();
    }
    if (platforms.empty()) {
        loadPlatform();
    }
    backgroundLayer.setPosition(window.mapPixelToCoords({ 0, 0 }));

    // 获取窗口的视图大小（即可视区域的大小）
    sf::Vector2f viewSize = view.getSize();

    // 大背景左上角始终为视图的左上角
    backgroundLayer.setScale(
        static_cast<float>(viewSize.x) / backgroundLayer.getLocalBounds().width,
        static_cast<float>(viewSize.y) / backgroundLayer.getLocalBounds().height
    );
    foregroundLayer.setPosition({ 0, 34.f });

    window.draw(backgroundLayer);
    window.draw(foregroundLayer);
}