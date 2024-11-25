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
