#include "Map.h"
#include <bits/stdc++.h>

Map::Map() {}

void Map::render(sf::RenderWindow& window, sf::View& view){
    if(!foregroundLayer.getTexture() || !backgroundLayer.getTexture()){
        loadMap();
    }
    if (platforms.empty()) {
        loadPlatform();
    }
    backgroundLayer.setPosition(window.mapPixelToCoords({0, 0}));

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

Platform::Platform(sf::Vector2f startPosition, float width) {
    this->startPosition = startPosition;
    this->width = width;
}

MR::MR() : Map() {

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

