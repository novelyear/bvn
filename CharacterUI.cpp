#include "CharacterUI.h"
#include "Constants.h"

CharacterUI::CharacterUI() {
	loadResources();
}

void CharacterUI::loadResources() {
    // 所有资源文件路径及其对应的键名
    std::unordered_map<std::string, std::string> resourcePaths = {
        {"qi_bar_0", "./access/others/shapes/qi_bar_0.png"},
        {"qi_bar_1", "./access/others/shapes/qi_bar_1.png"},
        {"qi_bar_2", "./access/others/shapes/qi_bar_2.png"},
        {"qi_bar_3", "./access/others/shapes/qi_bar_3.png"},
        {"qi_0", "./access/others/shapes/qi_0.png"},
        {"qi_1", "./access/others/shapes/qi_1.png"},
        {"qi_2", "./access/others/shapes/qi_2.png"},
        {"qi_3", "./access/others/shapes/qi_3.png"},
        {"middle", "./access/others/shapes/middle.png"},
        {"qi_bar", "./access/others/shapes/qi_bar.png"},
        {"avatar_box", "./access/others/shapes/avatar_box.png"},
        {"blood", "./access/others/shapes/blood.png"},
        {"blood_bar", "./access/others/shapes/blood_bar.png"},
        {"chakra", "./access/others/shapes/chakra.png"},
        {"chakra_bar", "./access/others/shapes/chakra_bar.png"},
        {"chakra_text", "./access/others/shapes/chakra_text.png"},
        {"chakra2", "./access/others/shapes/chakra2.png"}
    };
    std::set<std::string> fixedSet = {
        "avatar_box", "qi_bar", "blood_bar", "chakra_bar", "middle", "chakra_text"
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
            sprite.setPosition({ 1000.f, 1000.f }); // 方便之后遍历绘制，不需要的先画在远处
            dynamicSprites[key] = sprite;
        }
    }
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
// 视图宽度
float CharacterUI::getViewWidth(const sf::View& view) {
    return view.getSize().x;
}

void CharacterUI::update(Character* c, const sf::View& view) {
    sf::Vector2f viewTopLeft = getViewTopLeft(view);
    float viewWidth = getViewWidth(view);
    sf::Vector2f xy = { 100.f, 100.f };
    float scale = view.getSize().x / 800.f; // 660是最大视图宽度
    // 固定UI元件的位置
    xy = { 0.f, 0.f };
    fixedSprites["avatar_box"].setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * scale, viewTopLeft.y + xy.y * scale });
    fixedSprites["avatar_box"].setScale(c->real ? scale : -1.f * scale, scale);
    xy = { 0.f, 570.f };
    fixedSprites["qi_bar"].setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    fixedSprites["qi_bar"].setScale(c->real ? scale : -1.f * scale, scale);
    xy = { 100.f, 25.f };
    fixedSprites["blood_bar"].setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    fixedSprites["blood_bar"].setScale(c->real ? scale : -1.f * scale, scale);
    xy = { 102.f, 49.f };
    fixedSprites["chakra_bar"].setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    fixedSprites["chakra_bar"].setScale(c->real ? scale : -scale, scale);
    xy = { 363.f, 10.f };
    fixedSprites["middle"].setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    fixedSprites["middle"].setScale(c->real ? scale : -scale, scale);
    xy = { c->real ? 245.f : 515.5f, 49.f };
    fixedSprites["chakra_text"].setPosition({ viewTopLeft.x + xy.x * scale, viewTopLeft.y + xy.y * scale });
    fixedSprites["chakra_text"].setScale(scale, scale);
    // 清空动态绘制队列
    spriteQueue.clear();

    // 动态元件：血条
    float healthPercentage = static_cast<float>(c->health) / INIT_HEALTH;
    sf::Sprite& bloodBar = dynamicSprites["blood"];
    xy = { 106.f, 29.f };
    bloodBar.setScale(healthPercentage * (c->real ? 1.f : -1.f) * scale, scale);
    bloodBar.setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    spriteQueue.emplace_back(bloodBar);
    // 动态元件：chakra条
    float chakraPercentage = static_cast<float>(c->chakra) / MAX_CHAKRA;
    sf::Sprite& chakraBar = c->chakra < CHAKRA_L ? getSprite("chakra2") : getSprite("chakra");
    chakraBar.setScale(chakraPercentage * (c->real ? 1.f : -1.f) * scale, scale);
    xy = { 111.f, 52.4f };
    chakraBar.setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    spriteQueue.emplace_back(chakraBar);
    // 动态元件：气条、气段数字
    int qiLevel = c->qi / MAX_QI;
    float qiPercentage = static_cast<float>(c->qi % MAX_QI) / MAX_QI;
    if (qiLevel >= 3) {
        qiLevel = 3;
        qiPercentage = 1.f;
    }
    std::string qiKey = "qi_bar_" + std::to_string(qiLevel);
    std::string qiNum = "qi_" + std::to_string(qiLevel);
    sf::Sprite& qiBar = getSprite(qiKey);
    sf::Sprite& qiStage = getSprite(qiNum);
    xy = { 11.f, 576.f };
    qiBar.setScale(qiPercentage * (c->real ? 1.f : -1.f) * scale, scale);
    qiBar.setPosition({ viewTopLeft.x + (c->real ? 0.f : viewWidth) + xy.x * (c->real ? scale : -scale), viewTopLeft.y + xy.y * scale });
    spriteQueue.emplace_back(qiBar);
    xy = { c->real ? 156.f : 633.f, 575.f };
    qiStage.setScale(scale, scale);
    qiStage.setPosition({ viewTopLeft.x + xy.x * scale, viewTopLeft.y + xy.y * scale });
    spriteQueue.emplace_back(qiStage);
}

void CharacterUI::render(sf::RenderWindow& window) {
    // 绘制固定元件
    for (const auto& [key, sprite] : fixedSprites) {
        window.draw(sprite);
    }

    // 绘制动态元件
    for (const auto& sprite : spriteQueue) {
        window.draw(sprite);
    }
}
