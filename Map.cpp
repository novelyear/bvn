#include "Map.h"
#include <bits/stdc++.h>

Map::Map(){
    
}

void Map::loadMap(){
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

void Map::update(float positionX){
    
}

void Map::checkCollision(Character charactor){
    
}

void Map::render(sf::RenderWindow& window, sf::View& view){
    if(!foregroundLayer.getTexture() || !backgroundLayer.getTexture()){
        loadMap();
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
