#include "Map.h"
#include <bits/stdc++.h>

void Map::loadMap(){
    // ����Զ���ͽ�������
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

    // ����ƽ̨

}

void Map::update(float positionX){
    
}

void Map::checkCollision(Character charactor){
    
}

void Map::render(sf::RenderWindow& window, sf::View& view){
    if(!foregroundLayer.getTexture() || !backgroundLayer.getTexture()){
        loadMap();
    }

    // ��ȡ���ڵ���ͼ��С������������Ĵ�С��
    sf::Vector2f viewSize = view.getSize();

    // 1. ��Ⱦ�����㣺����ͼ��ʼ������������ڣ������㲻����ͼ���ƶ����仯
    backgroundLayer.setScale(
        static_cast<float>(viewSize.x) / backgroundLayer.getLocalBounds().width,
        static_cast<float>(viewSize.y) / backgroundLayer.getLocalBounds().height
    );

    window.draw(backgroundLayer);
    window.draw(foregroundLayer);
}
