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

    // ��ȡ���ڵ���ͼ��С������������Ĵ�С��
    sf::Vector2f viewSize = view.getSize();

    // �󱳾����Ͻ�ʼ��Ϊ��ͼ�����Ͻ�
    backgroundLayer.setScale(
        static_cast<float>(viewSize.x) / backgroundLayer.getLocalBounds().width,
        static_cast<float>(viewSize.y) / backgroundLayer.getLocalBounds().height
    );
    foregroundLayer.setPosition({ 0, 0 });

    window.draw(backgroundLayer);
    window.draw(foregroundLayer);
}
