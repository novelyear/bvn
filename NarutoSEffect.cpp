#include "NarutoS.h"
#include "Constants.h"
NarutoSEffect::NarutoSEffect() {
    //if (sharedAnchors.empty())
        loadResources(
            "D:\\D1\\code\\bvn\\access\\narutoS\\texture_effects_atlas.png",
            "D:\\D1\\code\\bvn\\access\\narutoS\\config\\effect_section.txt",
            "D:\\D1\\code\\bvn\\access\\narutoS\\config\\effect_origins.txt",
            "D:\\D1\\code\\bvn\\access\\narutoS\\effects_anchors.txt");
    sprite.setTexture(texture);
}

void NarutoSEffect::ki(sf::Vector2f position, bool left) {
    this->position = position;
    this->left = left;
    currentState = EffectState::KI_before;
    currentFrame = 0;
}

void NarutoSEffect::updatePosition(sf::View view) {
    if (currentState == EffectState::Default) return;

    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    // 获取视图的当前边界
    float left_border = center.x - size.x / 2.f;
    float right_border = center.x + size.x / 2.f;

    if (currentState == EffectState::KI_before) {
        position.x += left ? -U_VELOCITY : U_VELOCITY; // 水平发射出去
        position.y += U_VELOCITY;
        if (position.x < left_border || position.x > right_border) { // 离开边界则消失
            currentState = EffectState::Default;
            currentFrame = 0;
        }
        else if (position.y > Map::CHARACTER_BOTTOM) {
            currentState = EffectState::KI_miss;
            currentFrame = 0;
        }
    }
}

void NarutoSEffect::updateSprite(float deltaTime) {
    if (currentState == EffectState::Default) return;
    elapsedTime += deltaTime;
    if (elapsedTime > PLAYER_FRAME) {
        switch (currentState) {
        case EffectState::KI_before:
            sprite.setTextureRect(anchors[rangeMap[EffectState::KI_before].first + currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::KI_before].first + currentFrame]);
            currentFrame = (currentFrame + 1) % (rangeMap[EffectState::KI_before].second - rangeMap[EffectState::KI_before].first);
            break;
        case EffectState::KI_miss:
            sprite.setTextureRect(anchors[rangeMap[EffectState::KI_miss].first + currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::KI_miss].first + currentFrame]);
            currentFrame++;
            if (currentFrame + rangeMap[EffectState::KI_miss].first > rangeMap[EffectState::KI_miss].second) {
                currentState = EffectState::Default;
                currentFrame = 0;
            }
            break;
        case EffectState::KI_after:
            sprite.setTextureRect(anchors[rangeMap[EffectState::KI_after].first + currentFrame]);
            sprite.setOrigin(origins[rangeMap[EffectState::KI_after].first + currentFrame]);
            currentFrame++;
            if (currentFrame + rangeMap[EffectState::KI_after].first > rangeMap[EffectState::KI_after].second) {
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