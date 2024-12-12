#include "Pause.h"

void Pause::setPause(float duration, void* exclude = nullptr) {
    isPaused = true;
    pauseDuration = duration;
    elapsedPauseTime = 0.f;
    excludedSource = exclude; // 设置排除的触发源
}

void Pause::update(float deltaTime, std::queue<PauseEvent>& eventQueue) {
    // 处理暂停时间
    if (isPaused) {
        elapsedPauseTime += deltaTime;
        if (elapsedPauseTime >= pauseDuration) {
            isPaused = false;
            excludedSource = nullptr;
        }
    }

    // 处理事件队列
    while (!eventQueue.empty()) {
        PauseEvent event = eventQueue.front(); eventQueue.pop();
        handleEvent(event);
    }
}

bool Pause::isPausedFor(void* source = nullptr) const {
    if (!isPaused) return false;
    return excludedSource == nullptr || excludedSource != source;
}

void Pause::handleEvent(const PauseEvent& event) {
    //if (event.type == EventType::PauseRequest) {
    setPause(event.duration, event.excludeSource ? event.source : nullptr);
    //}
}
