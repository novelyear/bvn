#include "CameraShake.h"
#include <cmath>
#include <cstdlib>

CameraShake::CameraShake() : offset(0.f, 0.f), intensity(0.f), duration(0.f) {}

sf::Vector2f CameraShake::generateRandomOffset() const {
    // 生成范围内的随机偏移
    float y = (std::rand() / (float)RAND_MAX - 0.5f) * 2 * intensity;
    return sf::Vector2f(0.f, y);
}

void CameraShake::startShake(float shakeIntensity, float shakeDuration) {
    intensity = shakeIntensity;
    duration = shakeDuration;
    timer.restart();
}

sf::Vector2f CameraShake::update() {
    if (duration <= 0.f) {
        offset = sf::Vector2f(0.f, 0.f); // 停止震动时偏移为0
    }
    else {
        offset = generateRandomOffset();
        duration -= timer.restart().asSeconds();
    }
    return offset;
}

bool CameraShake::isShaking() const {
    return duration > 0.f;
}
