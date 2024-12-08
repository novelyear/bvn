#pragma once
#include <SFML/Graphics.hpp>
#include "Effect.h"
#include "Map.h"

class Effect;

class Character
{
public:
	static bool SameOr(bool a, bool b);
	static void separate(Character* a, Character* b);

	bool real;
	int health;
	int chakra;
	int qi;

	sf::Texture texture;
	std::vector<sf::IntRect> anchors;
	std::vector<sf::Vector2f> origins;
	std::pair<int, int> animation; // 开场动作
	std::pair<int, int> animation_win; // 开场动作
		
	std::pair<int, int> run; //跑动态
	std::pair<int, int> jumping; // 跃起上升态
	std::pair<int, int> fall; // 空中下落态
	std::pair<int, int> landed; // 着陆态
	std::pair<int, int> J1; // 一段普攻态
	std::pair<int, int> J2; // 二段普攻态
	std::pair<int, int> J3; // 三段普攻态
	std::pair<int, int> J4; // 四段普攻态
	std::pair<int, int> stand; // 站立态
	std::pair<int, int> hit; // 受击态
	std::pair<int, int> kick; // 击飞态:暂定
	std::pair<int, int> flashing; // 冲刺态
		
	std::pair<int, int> S; // 防御态，正放展开防御，倒放解开防御
	std::pair<int, int> KJ; // 空中普攻
	std::pair<int, int> WJ; // 普攻2
	std::pair<int, int> SJ; // 普攻3
	std::pair<int, int> KU; // 空中远攻
	std::pair<int, int> KU_down; // 空中远攻落地
	std::pair<int, int> SU; // 远攻3
	std::pair<int, int> SUU; // 远攻3，追加
	std::pair<int, int> WU; // 远攻2
	std::pair<int, int> WUU; // 远攻2，追加
	std::pair<int, int> U; // 远攻1
	std::pair<int, int> U_after; // 远攻1命中后（适用NarutoS）
	std::pair<int, int> SI_before; // 大招3释放
	std::pair<int, int> WI_before; // 大招2释放
	std::pair<int, int> I_before; // 大招1释放
	std::pair<int, int> KI; // 空中大

		
	std::pair<int, int> SI_after; // 大招3命中后
	std::pair<int, int> WI_after; // 大招2命中后
	std::pair<int, int> I_after; // 大招1命中后
		
	std::pair<int, int> SI_miss; // 大招3未命中
	std::pair<int, int> WI_miss; // 大招2未命中
	std::pair<int, int> I_miss; // 大招未命中

	CharacterState currentState;
	bool inAir; // 在空中
	bool left; // 朝向
	bool onBoard;
	int jumpTimes; // 跳跃次数
	int attackStage; // 普攻阶段
	float elapsedTime; // sprite纹理切换计时器
	sf::Clock hitTimer; // 受击检测间隔时钟
	CharacterState lastHit; // 上次被什么攻击打了
	int currentFrame;

	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::FloatRect rect;

	std::unique_ptr<EffectPool> effects;

	Character(); 
	virtual ~Character() = default; 

	void moveLeft(); 
	void moveRight();
	void jump();
	void down();
	void flash();

	void render(sf::RenderWindow& window);
	void updatePosition(sf::View view);
	void updateDirection(sf::Vector2f enemyPosition);
	void updateCollisionWithPlatform(std::vector<Platform> platforms);
	void updateCollisionWithEffect(Character* enemy);
	void gainVelocity(sf::Vector2f acceleration);

	virtual void j1();
	virtual void j2();
	virtual void j3();
	virtual void j4();
	virtual void kj();
	virtual void sj();
	virtual void su();
	virtual void suu();
	virtual void s();
	virtual void s_release();
	virtual void wj();
	virtual void wi();

	virtual void u();
	virtual void ku();
	virtual void si();
	virtual void i();
	virtual void ki();
	virtual void wu();
	virtual void wuu();

	virtual bool canTouch() = 0; // 人物本身能够无伤碰触的状态集
	virtual void update(float deltaTime, sf::View view, Character* enemy, std::vector<Platform> platforms) =0;
	virtual void loadResources(const std::string& directory, const std::string& rangeFile,
							   const std::string& originFile, const std::string& anchorFile) = 0;
	virtual void handleMove() =0;
	virtual void updateSprite(float deltaTime, sf::Vector2f enemyPosition) =0;
	
	virtual void updateCollisionWithEnemy(Character* enemy) = 0;

	virtual void exertEffect(Character * enemy, Effect * e) = 0;
	virtual void exertEffect(Character * enemy) = 0;
};

