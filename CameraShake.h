#pragma once
#include <SFML/System.hpp>

class CameraShake {
private:
    sf::Vector2f offset;      // ��ǰ����ƫ��
    float intensity;          // ��ǿ��
    float duration;           // ʣ�����ʱ��
    sf::Clock timer;          // ��ʱ��

    sf::Vector2f generateRandomOffset() const; // �������ƫ����

public:
    CameraShake();

    // �����𶯲�������ʼ��
    void startShake(float shakeIntensity, float shakeDuration);

    // ������Ч�������ص�ǰ��ƫ����
    sf::Vector2f update();

    // ������Ƿ����
    bool isShaking() const;
};

