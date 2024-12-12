#pragma once
#include "Character.h"

class Character;

class Pause {
private:
    bool isPaused = false;        // �Ƿ�����ͣ״̬
    float pauseDuration = 0.f;    // ��ͣ��ʣ��ʱ��
    float elapsedPauseTime = 0.f; // �Ѿ���ͣ��ʱ��
    void* excludedSource = nullptr; // ���ų��Ĵ���Դ

public:
    void setPause(float duration, void* exclude);
    void update(float deltaTime, std::queue<PauseEvent>& eventQueue);
    bool isPausedFor(void* source) const;




private:
    void handleEvent(const PauseEvent& event);
};



