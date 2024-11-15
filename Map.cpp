#include "Map.h"
#include <bits/stdc++.h>

void Map::loadMap(){
    // 加载远景和近景纹理
    if (!backgroundLayerTexture.loadFromFile("access\\bg.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    else {
        backgroundLayer.setTexture(backgroundLayerTexture);
    }

    if (!foregroundLayerTexture.loadFromFile("access\\building.png")) {
        std::cerr << "Failed to load foreground texture!" << std::endl;
    }
    else {
        foregroundLayer.setTexture(foregroundLayerTexture);
    }

    // 设置平台

}

void Map::update(float positionX){
    
}

void Map::checkCollision(Character charactor){
    
}

void Map::render(sf::RenderWindow& window, sf::View& view){
    if(!foregroundLayer.getTexture() || !backgroundLayer.getTexture()){
        loadMap();
    }

    // 获取窗口的视图大小（即可视区域的大小）
    sf::Vector2f viewSize = view.getSize();

    // 1. 渲染背景层：背景图像始终填充整个窗口，背景层不随视图的移动而变化
    backgroundLayer.setScale(
        static_cast<float>(viewSize.x) / backgroundLayer.getLocalBounds().width,
        static_cast<float>(viewSize.y) / backgroundLayer.getLocalBounds().height
    );

    window.draw(backgroundLayer);
    window.draw(foregroundLayer);
}
