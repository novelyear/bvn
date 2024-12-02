#include "Constants.h"
#include "Character.h"
#include "Gaara.h"

GaaraEffect::GaaraEffect() : Effect() {
    if(sharedAnchors.empty()) 
        loadResources(
        "D:\\D1\\code\\bvn\\access\\gaaraS\\texture_effects_atlas.png",
        "D:\\D1\\code\\bvn\\access\\gaaraS\\config\\effect_section.txt",
        "D:\\D1\\code\\bvn\\access\\gaaraS\\config\\effect_origins.txt",
        "D:\\D1\\code\\bvn\\access\\gaaraS\\effects_anchors.txt");
    texture = sharedTexture;
    anchors = sharedAnchors;
    origins = sharedOrigins;
    rangeMap = sharedRangeMap;
    sprite.setTexture(texture);
}

void GaaraEffect::u(sf::Vector2f rolePosition, bool left) {
    position = rolePosition;
    currentState = EffectState::U;
    currentFrame = 0;
    this->left = left;
}

void GaaraEffect::wu(sf::Vector2f rolePosition) {
    position = rolePosition;
    currentState = EffectState::WU;
    currentFrame = 0;
}

void GaaraEffect::si_before(sf::Vector2f tarPosition) {
    currentState = EffectState::SI_before;
    currentFrame = 0;
    position = tarPosition;
}

void GaaraEffect::i_before(sf::Vector2f tarPosition) {
    currentState = EffectState::I_before;
    currentFrame = 0;
    position = tarPosition;
}


void GaaraEffect::updatePosition(sf::View view) {
    if (currentState == EffectState::Default) return;

    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    // 获取视图的当前边界
    float left_border = center.x - size.x / 2.f;
    float right_border = center.x + size.x / 2.f;

    if (currentState == EffectState::U) {
        position.x += left ? -U_VELOCITY : U_VELOCITY; // 水平发射出去
        if (position.x < left_border || position.x > right_border) { // 离开边界则消失
            currentState = EffectState::Default;
            currentFrame = 0;
        }
    }
}

void GaaraEffect::updateSprite(float deltaTime) {
    if (currentState == EffectState::Default) return;
    elapsedTime += deltaTime;
    if (elapsedTime > PLAYER_FRAME) {
        switch (currentState) {
        case EffectState::U:
            sprite.setTextureRect(anchors[rangeMap[EffectState::U].first + currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::U].first + currentFrame]);
            currentFrame = (currentFrame + 1) % (rangeMap[EffectState::U].second - rangeMap[EffectState::U].first + 1); // TODO 有点问题
            break;
        case EffectState::WU:
            sprite.setTextureRect(anchors[rangeMap[EffectState::WU].first + currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::WU].first + currentFrame]);
            currentFrame++;
            if (currentFrame + rangeMap[EffectState::WU].first > rangeMap[EffectState::WU].second) {
                currentState = EffectState::Default;
                currentFrame = 0;
            }
            break;
        case EffectState::SI_before:
            sprite.setTextureRect(anchors[rangeMap[EffectState::SI_before].first + currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::SI_before].first + currentFrame]);
            currentFrame++;
            if (currentFrame + rangeMap[EffectState::SI_before].first > rangeMap[EffectState::SI_before].second) {
                currentState = EffectState::SI_miss;
                currentFrame = 0;
            }
            break;
        case EffectState::SI_miss:
            sprite.setTextureRect(anchors[rangeMap[EffectState::SI_miss].second - currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::SI_miss].second - currentFrame]);
            currentFrame++;
            if (rangeMap[EffectState::SI_miss].second - currentFrame < rangeMap[EffectState::SI_miss].first) {
                currentState = EffectState::Default;
                currentFrame = 0;
            }
            break;
        case EffectState::SI_after:
            sprite.setTextureRect(anchors[rangeMap[EffectState::SI_after].second - currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::SI_after].second - currentFrame]);
            currentFrame++;
            if (rangeMap[EffectState::SI_after].second - currentFrame < rangeMap[EffectState::SI_after].first) {
                currentState = EffectState::Default;
                currentFrame = 0;
            }
            break;
        case EffectState::I_before:
            sprite.setTextureRect(anchors[rangeMap[EffectState::I_before].second - currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::I_before].second - currentFrame]);
            currentFrame++;
            if (rangeMap[EffectState::I_before].second - currentFrame < rangeMap[EffectState::I_before].first) {
                currentState = EffectState::I_miss;
                currentFrame = 0;
            }
            break;
        case EffectState::I_miss:
            sprite.setTextureRect(anchors[rangeMap[EffectState::I_miss].second - currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::I_miss].second - currentFrame]);
            currentFrame++;
            if (rangeMap[EffectState::I_miss].second - currentFrame < rangeMap[EffectState::I_miss].first) {
                currentState = EffectState::Default;
                currentFrame = 0;
            }
            break;
        case EffectState::I_after:
            sprite.setTextureRect(anchors[rangeMap[EffectState::I_after].second - currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::I_after].second - currentFrame]);
            currentFrame++;
            if (rangeMap[EffectState::I_after].second - currentFrame < rangeMap[EffectState::I_after].first) {
                currentState = EffectState::Default;
                currentFrame = 0;
            }
            break;
        default:
            break;
        }
        elapsedTime = 0.f;
    }
    if (left)
        sprite.setScale(-1.f, 1.f); // 水平镜像，垂直保持不变
    else 
        sprite.setScale(1.f, 1.f);
    sprite.setPosition(position);
}