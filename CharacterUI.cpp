#include "CharacterUI.h"
#include "Constants.h"

CharacterUI::CharacterUI() {
	loadResources();
}

void CharacterUI::loadResources() {
    // 所有资源文件路径及其对应的键名
    std::unordered_map<std::string, std::string> resourcePaths = {
        {"qi_0", "D:/D1/code/bvn/access/others/shapes/qi_0.png"},
        {"qi_1", "D:/D1/code/bvn/access/others/shapes/qi_1.png"},
        {"qi_2", "D:/D1/code/bvn/access/others/shapes/qi_2.png"},
        {"qi_3", "D:/D1/code/bvn/access/others/shapes/qi_3.png"},
        {"qi_bar", "D:/D1/code/bvn/access/others/shapes/qi_bar.png"},
        {"avatar_box", "D:/D1/code/bvn/access/others/shapes/avatar_box.png"},
        {"blood", "D:/D1/code/bvn/access/others/shapes/blood.png"},
        {"blood_bar", "D:/D1/code/bvn/access/others/shapes/blood_bar.png"},
        {"chakra", "D:/D1/code/bvn/access/others/shapes/chakra.png"},
        {"chakra_bar", "D:/D1/code/bvn/access/others/shapes/chakra_bar.png"},
        {"chakra2", "D:/D1/code/bvn/access/others/shapes/chakra2.png"}
    };
    std::set<std::string> fixedSet = {
    "avatar_box", "qi_bar", "blood_bar", "chakra_bar"
    };
    for (const auto& [key, path] : resourcePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << std::endl;
            continue;
        }
        textures[key] = std::move(texture);

        sf::Sprite sprite(textures[key]);
        if (fixedSet.count(key) > 0) {
            // 固定元件
            fixedSprites[key] = sprite;
        }
        else {
            // 动态元件
            dynamicSprites[key] = sprite;
        }
    }

    // 设置固定元件的位置
    fixedSprites["avatar_box"].setPosition(10.f, 10.f); // 头像框
    fixedSprites["qi_bar"].setPosition(200.f, 10.f);   //  气条
    fixedSprites["blood_bar"].setPosition(0.f, 0.f);   // 血条
    fixedSprites["chakra_bar"].setPosition(50.f, 50.f);   // chakra条
}


sf::Sprite& CharacterUI::getSprite(const std::string& key) {
    auto it = dynamicSprites.find(key);
    if (it != dynamicSprites.end()) {
        return it->second;
    }
    throw std::runtime_error("Sprite not found: " + key);
}

// 获取视图左上角的坐标
sf::Vector2f CharacterUI::getViewTopLeft(const sf::View& view) const {
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();
    return { center.x - size.x / 2, center.y - size.y / 2 };
}

void CharacterUI::update(Character* c, const sf::View& view) {
    sf::Vector2f viewTopLeft = getViewTopLeft(view);

    // 固定UI元件的位置
    fixedSprites["avater_box"].setPosition(viewTopLeft + sf::Vector2f(10.f, 10.f)); // 示例位置
    fixedSprites["qi_bar"].setPosition(viewTopLeft + sf::Vector2f(200.f, 10.f));   // 示例位置
    fixedSprites["blood_bar"].setPosition(viewTopLeft + sf::Vector2f(100.f, 10.f));   // 示例位置
    fixedSprites["chakra_bar"].setPosition(viewTopLeft + sf::Vector2f(150.f, 10.f));   // 示例位置

    // 动态元件：血条
    float healthPercentage = static_cast<float>(c->health) / INIT_HEALTH;
    sf::Sprite& bloodBar = dynamicSprites["blood_bar"];
    bloodBar.setScale(healthPercentage, c->real ? 1.f : -1.f);
    bloodBar.setPosition(viewTopLeft + sf::Vector2f(100.f, 50.f)); // 示例位置

    // 动态元件：chakra条
    float chakraPercentage = static_cast<float>(c->chakra) / MAX_CHAKRA;
    sf::Sprite& chakraBar = c->chakra < CHAKRA_L ? getSprite("chakra") : getSprite("chakra2");
    chakraBar.setScale(chakraPercentage, c->real ? 1.f : -1.f);
    chakraBar.setPosition(viewTopLeft + sf::Vector2f(100.f, 100.f)); // 示例位置

    // 动态元件：气条
    int qiLevel = c->qi / MAX_QI;
    float qiPercentage = static_cast<float>(c->qi % MAX_QI) / MAX_QI;
    std::string qiKey = "qi_" + std::to_string(qiLevel);
    sf::Sprite& qiBar = getSprite(qiKey);
    qiBar.setScale(qiPercentage, c->real ? 1.f : -1.f);
    qiBar.setPosition(viewTopLeft + sf::Vector2f(100.f, 150.f)); // 示例位置
}

void CharacterUI::render(sf::RenderWindow& window) {
    // 绘制固定元件
    for (const auto& [key, sprite] : fixedSprites) {
        window.draw(sprite);
    }

    // 绘制动态元件
    for (const auto& [key, sprite] : dynamicSprites) {
        window.draw(sprite);
    }
}
