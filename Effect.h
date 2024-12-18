#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Enums.h"
class Effect {
public:
	void loadResources(const std::string& directory, const std::string& rangeFile,
		const std::string& originFile, const std::string& anchorFile);

	sf::Texture texture; // 纹理图集
	std::unordered_map<EffectState, std::pair<int, int>> rangeMap; // 技能组范围
	std::vector<sf::IntRect> anchors;  // 锚框集
	std::vector<sf::Vector2f> origins; // 原点集

	sf::Vector2f position; // 位置
	sf::Sprite sprite;


	int currentFrame;
	EffectState currentState;
	bool left;
	float elapsedTime;

	Effect();


	void update(float deltaTime, sf::View view);
	void render(sf::RenderWindow& window);
	virtual void u(sf::Vector2f point, bool left);
	virtual void wu(sf::Vector2f position);

	virtual void i_before(sf::Vector2f position);
	virtual void i_after(sf::Vector2f position);
	virtual void si_before(sf::Vector2f position);
	virtual void si_after(sf::Vector2f position);
	virtual void ki(sf::Vector2f position, bool left);
	virtual void flash_ash(sf::Vector2f position, bool left);
	virtual void landed(sf::Vector2f position)				;
	virtual void flash_air(sf::Vector2f position, bool left);
	virtual void i_effect(sf::Vector2f position);

	virtual void updatePosition(sf::View view) = 0;
	virtual void updateSprite(float deltaTime) = 0;
};

class EffectPool {
public:
	std::vector<std::unique_ptr<Effect>> effects;

	EffectPool();
	EffectPool(CharacterType c);// 初始化特效池

	void render(sf::RenderWindow& window);// 批量绘制effect

	void run(sf::Vector2f position, EffectState s, bool left);
	void updatePosition(sf::View view);
	void updateSprite(float deltaTime);
	void update(float deltaTime, sf::View view);
};

class DefaultEffect :
	public Effect {
public:
	DefaultEffect();

	void flash_ash(sf::Vector2f position, bool left) override;
	void landed(sf::Vector2f position)				 override;
	void flash_air(sf::Vector2f position, bool left) override;
	void i_effect(sf::Vector2f position) override;

	void updateSprite(float deltaTime) override;

	void updatePosition(sf::View view) override;
};