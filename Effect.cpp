#include "Effect.h"
#include "Gaara.h"
#include "NarutoS.h"
#include "Constants.h"

// 定义静态成员变量
sf::Texture Effect::sharedTexture;
std::unordered_map<EffectState, std::pair<int, int>> Effect::sharedRangeMap;
std::vector<sf::IntRect> Effect::sharedAnchors;
std::vector<sf::Vector2f> Effect::sharedOrigins;

EffectPool::EffectPool() {}

// 构造函数：初始化特效池，创建指定数量的默认特效对象
EffectPool::EffectPool(CharacterType c) {
    for (int i = 0; i < 8; ++i) {
        switch (c) {
            case CharacterType::Gaara:
                effects.push_back(std::make_unique<GaaraEffect>());
                break;
            case CharacterType::NarutoS:
                effects.push_back(std::make_unique<NarutoSEffect>());
                break;
            case CharacterType::Default:
                effects.push_back(std::make_unique<DefaultEffect>());
                break;
            default:
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
                case EffectState::I_after:
                    effect->i_after(position);
                    break;
                case EffectState::U:
                    effect->u(position, left);
                    break;
                case EffectState::SI_before:
                    effect->si_before(position);
                    break;
                case EffectState::SI_after:
                    effect->si_after(position);
                    break;
                case EffectState::WU:
                    effect->wu(position);
                    break;
                case EffectState::KI_before:
                    effect->ki(position, left);
                    break;
                case EffectState::Flash_air:
                    effect->flash_air(position, left);
                    break;
                case EffectState::Flash_ash:
                    effect->flash_ash(position, left);
                    break;
                case EffectState::Landed_ash:
                    effect->landed(position);
                    break;
                case EffectState::I_effect:
                    effect->i_effect(position);
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

// ========Effect========
Effect::Effect() {
    currentState = EffectState::Default;
    currentFrame = 0;
    elapsedTime = 0.f;
    left = true;
}

void Effect::u(sf::Vector2f point, bool left)     {printf("you didn't override the function!\n");}
void Effect::wu(sf::Vector2f position)            {printf("you didn't override the function!\n");}
void Effect::i_before(sf::Vector2f position)      {printf("you didn't override the function!\n");}
void Effect::i_after(sf::Vector2f position)       {printf("you didn't override the function!\n");}
void Effect::si_before(sf::Vector2f position)     {printf("you didn't override the function!\n");}
void Effect::si_after(sf::Vector2f position)      {printf("you didn't override the function!\n");}
void Effect::ki(sf::Vector2f position, bool left) {printf("you didn't override the function!\n");}
void Effect::flash_air(sf::Vector2f position, bool left) {
    currentState = EffectState::Flash_air;
    currentFrame = 0;
    this->position = position;
    this->left = left;
}
void Effect::flash_ash(sf::Vector2f position, bool left) {
    currentState = EffectState::Flash_ash;
    currentFrame = 0;
    this->position = position;
    this->left = left;
}
void Effect::landed(sf::Vector2f position) {
    currentState = EffectState::Landed_ash;
    currentFrame = 0;
    this->position = position;
}
void Effect::i_effect(sf::Vector2f position) {
    currentState = EffectState::I_effect;
    currentFrame = 0;
    this->position = position;
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
    sharedOrigins.resize(1); // 留出0号
    std::ifstream originInput(originFile);
    if (!originInput.is_open()) {
        std::cerr << "Failed to open origin file: " << originFile << std::endl;
        return;
    }

    int index;
    float x, y;
    char delimiter;
    while (originInput >> index >> delimiter >> delimiter >> x >> delimiter >> y >> delimiter) {
        if (index >= sharedOrigins.size()) {
            sharedOrigins.resize(index + 1);
        }
        sharedOrigins[index] = sf::Vector2f(x, y);
    }
    originInput.close();

    // 读取 anchorFile
    sharedAnchors.resize(1); // 留出0号
    std::ifstream anchorInput(anchorFile);
    if (!anchorInput.is_open()) {
        std::cerr << "Failed to open anchor file: " << anchorFile << std::endl;
        return;
    }

    int x1, y1, width, height;
    while (anchorInput >> index >> delimiter >> delimiter >> x1 >> delimiter >> y1 >> delimiter >> width >> delimiter >> height >> delimiter) {
        if (index >= sharedAnchors.size()) {
            sharedAnchors.resize(index + 1);
        }
        sharedAnchors[index] = sf::IntRect(x1, y1, width, height);
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
            if (type == "SU") sharedRangeMap[EffectState::SU] = std::make_pair(start, end);
            else if (type == "WU") sharedRangeMap[EffectState::WU] = std::make_pair(start, end);
            else if (type == "U") sharedRangeMap[EffectState::U] = std::make_pair(start, end);
            else if (type == "SI_before") sharedRangeMap[EffectState::SI_before] = std::make_pair(start, end);
            else if (type == "WI_before") sharedRangeMap[EffectState::WI_before] = std::make_pair(start, end);
            else if (type == "I_before") sharedRangeMap[EffectState::I_before] = std::make_pair(start, end);
            else if (type == "SI_after") sharedRangeMap[EffectState::SI_after] = std::make_pair(start, end);
            else if (type == "WI_after") sharedRangeMap[EffectState::WI_after] = std::make_pair(start, end);
            else if (type == "I_after") sharedRangeMap[EffectState::I_after] = std::make_pair(start, end);
            else if (type == "SI_miss") sharedRangeMap[EffectState::SI_miss] = std::make_pair(start, end);
            else if (type == "WI_miss") sharedRangeMap[EffectState::WI_miss] = std::make_pair(start, end);
            else if (type == "I_miss") sharedRangeMap[EffectState::I_miss] = std::make_pair(start, end);
            else if (type == "KI_before") sharedRangeMap[EffectState::KI_before] = std::make_pair(start, end);
            else if (type == "KI_after") sharedRangeMap[EffectState::KI_after] = std::make_pair(start, end);
            else if (type == "KI_miss") sharedRangeMap[EffectState::KI_miss] = std::make_pair(start, end);
            else if (type == "I_effect") sharedRangeMap[EffectState::I_effect] = std::make_pair(start, end);
            else if (type == "flash_air") sharedRangeMap[EffectState::Flash_air] = std::make_pair(start, end);
            else if (type == "flash_ash") sharedRangeMap[EffectState::Flash_ash] = std::make_pair(start, end);
            else if (type == "Landed_ash") sharedRangeMap[EffectState::Landed_ash] = std::make_pair(start, end);
        }
        else {
            std::cerr << "Invalid range line: " << line << std::endl;
        }
    }
    rangeInput.close();

    // 加载纹理（假设 directory 目录下是一个完整的纹理图集）
    if (!sharedTexture.loadFromFile(directory)) {
        std::cerr << "Failed to load sharedTexture from directory: " << directory << std::endl;
    }
    sprite.setTexture(Effect::sharedTexture);
    sprite.setTextureRect(Effect::sharedAnchors[20]); // 硬编码，20号图是空，防止首次按下时正好未逻辑换帧导致闪烁全图
                                                      // 只适用于我爱罗，后面可改为0号
}
// ========DefaultEffectPool========
DefaultEffect::DefaultEffect() {
    loadResources(
        "./access/others/defaultE_textures_atlas.png",
        "./access/others/config/effect_section.txt",
        "./access/others/config/effect_origins.txt",
        "./access/others/defaultE_anchors.txt"
    );
    texture = sharedTexture;
    anchors = sharedAnchors;
    origins = sharedOrigins;
    rangeMap = sharedRangeMap;
    sprite.setTexture(texture);
}
void DefaultEffect::flash_ash(sf::Vector2f position, bool left) {
    currentState = EffectState::Flash_ash;
    currentFrame = 0;
    this->position = position;
    this->left = left;
}
void DefaultEffect::landed(sf::Vector2f position) {
    currentState = EffectState::Landed_ash;
    currentFrame = 0;
    this->position = position;
}
void DefaultEffect::flash_air(sf::Vector2f position, bool left) {
    currentState = EffectState::Flash_air;
    currentFrame = 0;
    this->position = position;
    this->left = left;
}

void DefaultEffect::i_effect(sf::Vector2f position) {
    currentState = EffectState::I_effect;
    currentFrame = 0;
    this->position = position;
}

void DefaultEffect::updateSprite(float deltaTime) {
    if (currentState == EffectState::Default) return;
    elapsedTime += deltaTime;
    if (elapsedTime > PLAYER_FRAME) {
        switch (currentState) {
            case EffectState::Flash_air:
                sprite.setTextureRect(anchors[rangeMap[EffectState::Flash_air].first + currentFrame]);
                sprite.setOrigin(origins[rangeMap[EffectState::Flash_air].first + currentFrame]);
                currentFrame++;
                if (currentFrame + rangeMap[EffectState::Flash_air].first > rangeMap[EffectState::Flash_air].second) {
                    currentState = EffectState::Default;
                    currentFrame = 0;
                }
                break;
            case EffectState::Flash_ash:
                sprite.setTextureRect(anchors[rangeMap[EffectState::Flash_ash].first + currentFrame]);
                sprite.setOrigin(origins[rangeMap[EffectState::Flash_ash].first + currentFrame]);
                currentFrame++;
                if (currentFrame + rangeMap[EffectState::Flash_ash].first > rangeMap[EffectState::Flash_ash].second) {
                    currentState = EffectState::Default;
                    currentFrame = 0;
                }
                break;
            case EffectState::Landed_ash:
                sprite.setTextureRect(anchors[rangeMap[EffectState::Landed_ash].first + currentFrame]);
                sprite.setOrigin(origins[rangeMap[EffectState::Landed_ash].first + currentFrame]);
                currentFrame++;
                if (currentFrame + rangeMap[EffectState::Landed_ash].first > rangeMap[EffectState::Landed_ash].second) {
                    currentState = EffectState::Default;
                    currentFrame = 0;
                }
                break;
            case EffectState::I_effect:
                sprite.setTextureRect(anchors[rangeMap[EffectState::I_effect].first + currentFrame]);
                sprite.setOrigin(origins[rangeMap[EffectState::I_effect].first + currentFrame]);
                currentFrame++;
                if (currentFrame + rangeMap[EffectState::I_effect].first > rangeMap[EffectState::I_effect].second) {
                    currentState = EffectState::Default;
                    currentFrame = 0;
                }
                break;
        }
        if (left)
            sprite.setScale(-1.f, 1.f); // 水平镜像，垂直保持不变
        else
            sprite.setScale(1.f, 1.f);
        sprite.setPosition(position);
    }
}
void DefaultEffect::updatePosition(sf::View view) {}