#include "Gaara.h"
#include <bits/stdc++.h>
#include "Constants.h"

Gaara::Gaara() : Character() {
    name = CharacterType::Gaara;
    real = true;
	left = false;
	position = { 100.f, Map::GROUND };
    effects = std::make_unique<EffectPool>(CharacterType::Gaara);
    defaultEffects = std::make_unique<EffectPool>(CharacterType::Default);
	loadResources(
		"D:\\D1\\code\\bvn\\access\\gaaraS\\texture_atlas.png",
		"D:\\D1\\code\\bvn\\access\\gaaraS\\config\\section.txt",
		"D:\\D1\\code\\bvn\\access\\gaaraS\\config\\origins.txt",
		"D:\\D1\\code\\bvn\\access\\gaaraS\\anchors.txt");
}

Gaara::Gaara(int flag) : Character() {
    name = CharacterType::Gaara;
    real = false;
	left = true;
	position = { 300.f, Map::GROUND };
	loadResources(
		"D:\\D1\\code\\bvn\\access\\gaaraS\\texture_atlas.png",
		"D:\\D1\\code\\bvn\\access\\gaaraS\\config\\section.txt",
		"D:\\D1\\code\\bvn\\access\\gaaraS\\config\\origins.txt",
		"D:\\D1\\code\\bvn\\access\\gaaraS\\anchors.txt");
    effects = std::make_unique<EffectPool>(CharacterType::Gaara);
    defaultEffects = std::make_unique<EffectPool>(CharacterType::Default);
}

bool Gaara::canTouch() {
    return (
        currentState == CharacterState::Stand || currentState == CharacterState::Running ||
        currentState == CharacterState::WU || currentState == CharacterState::Jumping ||
        currentState == CharacterState::Fall || currentState == CharacterState::S_Release ||
        currentState == CharacterState::I_miss || currentState == CharacterState::SI_miss ||
        currentState == CharacterState::WI_miss || currentState == CharacterState::Hit ||
        currentState == CharacterState::Kick || (currentState == CharacterState::U && currentFrame > 11)||
        currentState == CharacterState::Landed || currentState == CharacterState::S
        );
}

void Gaara::loadResources(const std::string& directory, const std::string& rangeFile, const std::string& originFile, const std::string& anchorFile) {
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
            if (type == "animation") animation = std::make_pair(start, end);
            else if (type == "animation_win") animation_win = std::make_pair(start, end);
            else if (type == "run") run = std::make_pair(start, end);
            else if (type == "jump") jumping = std::make_pair(start, end);
            else if (type == "fall") fall = std::make_pair(start, end);
            else if (type == "landed") landed = std::make_pair(start, end);
            else if (type == "J1") J1 = std::make_pair(start, end);
            else if (type == "J2") J2 = std::make_pair(start, end);
            else if (type == "J3") J3 = std::make_pair(start, end);
            else if (type == "stand") stand = std::make_pair(start, end);
            else if (type == "hit") hit = std::make_pair(start, end);
            else if (type == "kick") kick = std::make_pair(start, end);
            else if (type == "flash") flashing = std::make_pair(start, end);
            else if (type == "S") S = std::make_pair(start, end);
            else if (type == "KJ") KJ = std::make_pair(start, end);
            else if (type == "WJ") WJ = std::make_pair(start, end);
            else if (type == "SJ") SJ = std::make_pair(start, end);
            else if (type == "KU") KU = std::make_pair(start, end);
            else if (type == "SU") SU = std::make_pair(start, end);
            else if (type == "WU") WU = std::make_pair(start, end);
            else if (type == "U") U = std::make_pair(start, end);
            else if (type == "SI_before") SI_before = std::make_pair(start, end);
            else if (type == "WI_before") WI_before = std::make_pair(start, end);
            else if (type == "I_before") I_before = std::make_pair(start, end);
            else if (type == "SI_after") SI_after = std::make_pair(start, end);
            else if (type == "WI_after") WI_after = std::make_pair(start, end);
            else if (type == "I_after") I_after = std::make_pair(start, end);
            else if (type == "SI_miss") SI_miss = std::make_pair(start, end);
            else if (type == "WI_miss") WI_miss = std::make_pair(start, end);
            else if (type == "I_miss") I_miss = std::make_pair(start, end);
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
    sprite.setTextureRect(anchors[1]);
}








