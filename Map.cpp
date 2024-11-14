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
    // 根据角色的位置动态调整近景的缩放比例
    float distance = std::abs(positionX - foregroundLayer.getPosition().x);
    scaleFactor = std::min(maxScale, 1.0f + (1.0f / (distance + 1)));  // 随着距离增大，缩小

    // 更新背景的缩放
    foregroundLayer.setScale(scaleFactor, scaleFactor);

    // 更新平台的缩放和位置
    //for (auto& platform : platforms) {
    //    platform.update(positionX * 0.5f, scaleFactor);  // 使平台和近景一起缩放
    //}
}

void Map::checkCollision(Character charactor){
    
}

void Map::render(sf::RenderWindow& window){
    if(!foregroundLayer.getTexture()){
        loadMap();
    }
    // 渲染远景（始终不动）
    window.draw(backgroundLayer);

    // 渲染近景（根据角色与背景的距离缩放）
    window.draw(foregroundLayer);
}
