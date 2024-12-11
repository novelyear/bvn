#pragma once
#include <SFML/System.hpp>

class CameraShake {
private:
    sf::Vector2f offset;      // 当前的震动偏移
    float intensity;          // 震动强度
    float duration;           // 剩余的震动时间
    sf::Clock timer;          // 计时器

    sf::Vector2f generateRandomOffset() const; // 生成随机偏移量

public:
    CameraShake();

    // 设置震动参数并开始震动
    void startShake(float shakeIntensity, float shakeDuration);

    // 更新震动效果，返回当前的偏移量
    sf::Vector2f update();

    // 检查震动是否结束
    bool isShaking() const;
};

