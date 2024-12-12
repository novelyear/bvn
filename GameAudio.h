#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <queue>

class GameAudio {
public:
    GameAudio();
    ~GameAudio();

    // 加载音效和音乐
    void loadSound(const std::string& key, const std::string& filepath);
    void loadMusic(const std::string& key, const std::string& filepath);

    // 播放音效
    void playSound(const std::string& key);
    void stopSound(const std::string& key);

    // 播放背景音乐
    void playMusic(const std::string& key, bool loop = true);
    void stopMusic();

    // 设置音量
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);

private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers; // 音效缓冲
    std::unordered_map<std::string, sf::Sound> sounds;             // 音效对象
    std::unordered_map<std::string, std::string> musicFiles;       // 音乐文件路径
    sf::Music music;                                               // 当前背景音乐

    float musicVolume = 40.f;
    float soundVolume = 50.f;
};


