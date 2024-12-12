#pragma once
// 世界底部
#define GROUND 600.f
// 角色兜底线
#define CHARACTER_BOTTOM 550.f
// 世界左部
#define LEFT_BORDER 0.f
// 世界右部
#define RIGHT_BORDER 800.f
// 视图双盒子模型间距 margin
#define PUSH_MARGIN 100.f

// 重力加速度
#define GRAVITY 0.25f
// 起跳初速度
#define JUMP_VELOCITY -7.f
// AD移动速度
#define MOVE_VELOCITY 3.5f
// 最大坠落速度
#define MAX_FALLING_VELOCITY 4.f
// 二段跳限制速度
#define LIMIT_V JUMP_VELOCITY + 2.5f
// 冲刺速度
#define FLASH_VELOCITY 7.f
// 我爱罗U飞行速度
#define U_VELOCITY 5.f
// 碰撞检测误差容忍
#define TOLERANCE 4.f


// 互斥力常数
#define REPULSION 57.f
// 人物初始生命值
#define INIT_HEALTH 1000


// 人物贴图轮换帧率
#define PLAYER_FRAME 0.034f

// 每次冲刺消耗的chakra
#define CHAKRA_L (40)
// chakra上限
#define MAX_CHAKRA (100)
// 气每段的上限
#define MAX_QI (100)

// 攻击检测间隔时间，短了可能导致大招末段伤害漏检
#define HIT_INTERVAL 0.35f

// 受击震屏时间
#define SHAKE_KICK 0.1f
// 受击暂停时间
#define PAUSE_KICK 0.3f
// 受击震屏幅度
#define AMPLITUDE 6.f