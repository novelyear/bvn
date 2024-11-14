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
    // ���ݽ�ɫ��λ�ö�̬�������������ű���
    float distance = std::abs(positionX - foregroundLayer.getPosition().x);
    scaleFactor = std::min(maxScale, 1.0f + (1.0f / (distance + 1)));  // ���ž���������С

    // ���±���������
    foregroundLayer.setScale(scaleFactor, scaleFactor);

    // ����ƽ̨�����ź�λ��
    //for (auto& platform : platforms) {
    //    platform.update(positionX * 0.5f, scaleFactor);  // ʹƽ̨�ͽ���һ������
    //}
}

void Map::checkCollision(Character charactor){
    
}

void Map::render(sf::RenderWindow& window){
    if(!foregroundLayer.getTexture()){
        loadMap();
    }
    // ��ȾԶ����ʼ�ղ�����
    window.draw(backgroundLayer);

    // ��Ⱦ���������ݽ�ɫ�뱳���ľ������ţ�
    window.draw(foregroundLayer);
}
