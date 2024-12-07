#include "NarutoS.h"
#include "Constants.h"

NarutoS::NarutoS() : Character() {
	real = true;
	left = false;
	position = { 100.f, GROUND };
	effects = std::make_unique<EffectPool>(CharacterType::NarutoS);
	loadResources(
		"D:\\D1\\code\\bvn\\access\\narutoS\\texture_atlas.png",
		"D:\\D1\\code\\bvn\\access\\narutoS\\config\\section.txt",
		"D:\\D1\\code\\bvn\\access\\narutoS\\config\\origins.txt",
		"D:\\D1\\code\\bvn\\access\\narutoS\\anchors.txt");
}

NarutoS::NarutoS(int flag) : Character() {
	real = false;
	left = true;
	position = { 300.f, GROUND };
	loadResources(
		"D:\\D1\\code\\bvn\\access\\narutoS\\texture_atlas.png",
		"D:\\D1\\code\\bvn\\access\\narutoS\\config\\section.txt",
		"D:\\D1\\code\\bvn\\access\\narutoS\\config\\origins.txt",
		"D:\\D1\\code\\bvn\\access\\narutoS\\anchors.txt");
	effects = std::make_unique<EffectPool>(CharacterType::NarutoS);
}

bool NarutoS::canTouch() {
	return (
		currentState == CharacterState::Stand || currentState == CharacterState::Running ||
		currentState == CharacterState::Jumping || currentState == CharacterState::Fall ||
		currentState == CharacterState::S_Release || currentState == CharacterState::Hit ||
		currentState == CharacterState::Kick || currentState == CharacterState::KI
		);
}

void NarutoS::loadResources(const std::string& directory, const std::string& rangeFile, const std::string& originFile, const std::string& anchorFile) {
    // ��ȡ originFile
    origins.resize(1); // ����0��
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

    // ��ȡ anchorFile
    anchors.resize(1); // ����0��
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

    // ��ȡ rangeFile
    std::ifstream rangeInput(rangeFile);
    if (!rangeInput.is_open()) {
        std::cerr << "Failed to open range file: " << rangeFile << std::endl;
        return;
    }

    std::string line, type;
    int start, end;
    while (std::getline(rangeInput, line)) {
        // �������ͺͷ�Χ
        char temp[256];
        if (sscanf_s(line.c_str(), "%[^-]-[%d,%d]", temp, static_cast<unsigned>(sizeof(temp)), &start, &end) == 3) {
            type = std::string(temp);

            // Ӳ����󶨵���ĳ�Ա����
            if (type == "animation") animation = std::make_pair(start, end);
            else if (type == "animation_win") animation_win = std::make_pair(start, end);
            else if (type == "run") run = std::make_pair(start, end);
            else if (type == "jump") jumping = std::make_pair(start, end);
            else if (type == "fall") fall = std::make_pair(start, end);
            else if (type == "landed") landed = std::make_pair(start, end);
            else if (type == "J1") J1 = std::make_pair(start, end);
            else if (type == "J2") J2 = std::make_pair(start, end);
            else if (type == "J3") J3 = std::make_pair(start, end);
            else if (type == "J4") J4 = std::make_pair(start, end);
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
            else if (type == "SUU") SUU = std::make_pair(start, end);
            else if (type == "WU") WU = std::make_pair(start, end);
            else if (type == "WUU") WUU = std::make_pair(start, end);
            else if (type == "U") U = std::make_pair(start, end);
            else if (type == "U_after") U_after = std::make_pair(start, end);
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

    // ������������ directory Ŀ¼����һ������������ͼ����
    if (!texture.loadFromFile(directory)) {
        std::cerr << "Failed to load texture from directory: " << directory << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(anchors[1]);
}