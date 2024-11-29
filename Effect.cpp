#include "Effect.h"
#include "Gaara.h"

EffectPool::EffectPool() {}

// 构造函数：初始化特效池，创建指定数量的默认特效对象
EffectPool::EffectPool(CharacterType c) {
    for (int i = 0; i < 3; ++i) {
        switch (c) {
            case CharacterType::Gaara:
            effects.push_back(std::make_unique<GaaraEffect>());
            break;
            case CharacterType::NarutoS:
                break;
        }
    }
}

// 批量绘制特效
void EffectPool::render(sf::RenderWindow& window) {
    for (const auto& effect : effects) {
        if (effect->currentState != EffectState::Default) {
            effect->render(window); // 只有非默认状态的特效需要绘制
        }
    }
}

// 特效的触发逻辑
void EffectPool::run(sf::Vector2f position, EffectState e, bool left) {
    for (const auto& effect : effects) {
        if (effect->currentState == EffectState::Default) {
            switch (e) {
                case EffectState::I_before: 
                    effect->i_before(position);
                    break;
                case EffectState::U:
                    effect->u(position, left);
                    break;
                case EffectState::SI_before:
                    effect->si_before(position);
                    break;
                default:
                    break;
            }
            return;
        }
    }
    printf("池满，注意回收\n");
}

void EffectPool::updatePosition(sf::View view) {
    for (const auto& effect : effects) {
        if (effect->currentState != EffectState::Default) {
            effect->updatePosition(view);
        }
    }
}
void EffectPool::updateSprite(float deltaTime) {
    for (const auto& effect : effects) {
        if (effect->currentState != EffectState::Default) {
            effect->updateSprite(deltaTime);
        }
    }
}

void EffectPool::update(float deltaTime, sf::View view) {
    for (const auto& effect : effects) {
        if (effect->currentState != EffectState::Default) {
            effect->updatePosition(view);
            effect->updateSprite(deltaTime);
        }
    }
}


Effect::Effect() {
    currentState = EffectState::Default;
    currentFrame = 0;
    elapsedTime = 0.f;
    left = true;
}


void Effect::update(float deltaTime, sf::View view){
    updatePosition(view);
    updateSprite(deltaTime);
}

void Effect::render(sf::RenderWindow& window){
    if (currentState != EffectState::Default) {
        window.draw(sprite);
    }
}

void Effect::loadResources(const std::string& directory, const std::string& rangeFile, const std::string& originFile, const std::string& anchorFile) {
    // 读取 originFile
    origins.resize(1); // 留出0号
    std::ifstream originInput(originFile);
    if (!originInput.is_open()) {
        std::cerr << "Failed to open origin file: " << originFile << std::endl;
        return;
    }

    int index;
    float x, y;
    char delimiter;
    while (originInput >> index >> delimiter >> delimiter >> x >> delimiter >> y >> delimiter) {
        if (index >= origins.size()) {
            origins.resize(index + 1);
        }
        origins[index] = sf::Vector2f(x, y);
    }
    originInput.close();

    // 读取 anchorFile
    anchors.resize(1); // 留出0号
    std::ifstream anchorInput(anchorFile);
    if (!anchorInput.is_open()) {
        std::cerr << "Failed to open anchor file: " << anchorFile << std::endl;
        return;
    }

    int x1, y1, width, height;
    while (anchorInput >> index >> delimiter >> delimiter >> x1 >> delimiter >> y1 >> delimiter >> width >> delimiter >> height >> delimiter) {
        if (index >= anchors.size()) {
            anchors.resize(index + 1);
        }
        anchors[index] = sf::IntRect(x1, y1, width, height);
    }
    anchorInput.close();

    // 读取 rangeFile
    std::ifstream rangeInput(rangeFile);
    if (!rangeInput.is_open()) {
        std::cerr << "Failed to open range file: " << rangeFile << std::endl;
        return;
    }

    std::string line, type;
    int start, end;
    while (std::getline(rangeInput, line)) {
        // 解析类型和范围
        char temp[256];
        if (sscanf_s(line.c_str(), "%[^-]-[%d,%d]", temp, static_cast<unsigned>(sizeof(temp)), &start, &end) == 3) {
            type = std::string(temp);

            // 硬编码绑定到类的成员变量
            if (type == "SU") rangeMap[EffectState::SU] = std::make_pair(start, end);
            else if (type == "WU") rangeMap[EffectState::WU] = std::make_pair(start, end);
            else if (type == "U") rangeMap[EffectState::U] = std::make_pair(start, end);
            else if (type == "SI_before") rangeMap[EffectState::SI_before] = std::make_pair(start, end);
            else if (type == "WI_before") rangeMap[EffectState::WI_before] = std::make_pair(start, end);
            else if (type == "I_before") rangeMap[EffectState::I_before] = std::make_pair(start, end);
            else if (type == "SI_after") rangeMap[EffectState::SI_after] = std::make_pair(start, end);
            else if (type == "WI_after") rangeMap[EffectState::WI_after] = std::make_pair(start, end);
            else if (type == "I_after") rangeMap[EffectState::I_after] = std::make_pair(start, end);
            else if (type == "SI_miss") rangeMap[EffectState::SI_miss] = std::make_pair(start, end);
            else if (type == "WI_miss") rangeMap[EffectState::WI_miss] = std::make_pair(start, end);
            else if (type == "I_miss") rangeMap[EffectState::I_miss] = std::make_pair(start, end);
            else if (type == "KI") rangeMap[EffectState::KI] = std::make_pair(start, end);
        }
        else {
            std::cerr << "Invalid range line: " << line << std::endl;
        }
    }
    rangeInput.close();

    // 加载纹理（假设 directory 目录下是一个完整的纹理图集）
    if (!texture.loadFromFile(directory)) {
        std::cerr << "Failed to load texture from directory: " << directory << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(anchors[20]); // 硬编码，20号图是空，防止首次按下时正好未逻辑换帧导致闪烁全图
}

