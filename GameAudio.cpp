#include "GameAudio.h"
#include <bits/stdc++.h>

GameAudio::GameAudio() : musicVolume(50.f), soundVolume(50.f) {}

GameAudio::~GameAudio() {
    stopMusic();
}

void GameAudio::loadSound(const std::string& key, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound: " << filepath << std::endl;
        return;
    }
    soundBuffers[key] = buffer;
    sf::Sound sound;
    sound.setBuffer(soundBuffers[key]);
    sounds[key] = sound;
}

void GameAudio::loadMusic(const std::string& key, const std::string& filepath) {
    musicFiles[key] = filepath;
}

void GameAudio::playSound(const std::string& key) {
    auto it = sounds.find(key);
    if (it != sounds.end()) {
        it->second.setVolume(soundVolume);
        it->second.play();
    }
}

void GameAudio::stopSound(const std::string& key) {
    auto it = sounds.find(key);
    if (it != sounds.end()) {
        it->second.stop();
    }
}

void GameAudio::playMusic(const std::string& key, bool loop) {
    if (music.getStatus() == sf::Music::Playing) return;
    auto it = musicFiles.find(key);
    if (it != musicFiles.end()) {
        if (!music.openFromFile(it->second)) {
            std::cerr << "Failed to load music: " << it->second << std::endl;
            return;
        }
        music.setVolume(musicVolume);
        music.setLoop(loop);
        music.play();
    }
}

void GameAudio::stopMusic() {
    music.stop();
}

void GameAudio::setMusicVolume(float volume) {
    musicVolume = volume;
    music.setVolume(volume);
}

void GameAudio::setSoundVolume(float volume) {
    soundVolume = volume;
    for (auto& pair : sounds) {
        pair.second.setVolume(volume);
    }
}
