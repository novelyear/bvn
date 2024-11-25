#include "MR.h"
#include <bits/stdc++.h>

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
    platforms.push_back(Platform({0, 550}, 800));
    platforms.push_back(Platform({45, 470}, 715));
    platforms.push_back(Platform({80, 380}, 637));
    platforms.push_back(Platform({75, 280}, 635));
    platforms.push_back(Platform({160, 200}, 470));
    platforms.push_back(Platform({175, 105}, 435));
}

