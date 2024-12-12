#pragma once
#include "Character.h"

class Character;

class Pause {
private:
    bool isPaused = false;        // 是否处于暂停状态
    float pauseDuration = 0.f;    // 暂停的剩余时间
    float elapsedPauseTime = 0.f; // 已经暂停的时间
    void* excludedSource = nullptr; // 被排除的触发源

public:
    void setPause(float duration, void* exclude);
    void update(float deltaTime, std::queue<PauseEvent>& eventQueue);
    bool isPausedFor(void* source) const;




private:
    void handleEvent(const PauseEvent& event);
};



