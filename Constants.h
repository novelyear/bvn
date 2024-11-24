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
#define GRAVITY 0.0025f
// 起跳初速度
#define JUMP_VELOCITY -0.9f
// AD移动速度
#define MOVE_VELOCITY 0.25f
// 最大坠落速度
#define MAX_FALLING_VELOCITY 0.3f
// 二段跳限制速度
#define LIMIT_V JUMP_VELOCITY + 0.45f
// 冲刺速度
#define FLASH_VELOCITY 2.5f
// 互斥力常数
#define REPULSION 5.f
// 碰撞检测误差容忍
#define TOLERANCE 2.f
// 人物初始生命值
#define INIT_HEALTH 100
// 人物贴图轮换帧率
#define PLAYER_FRAME 0.034f
