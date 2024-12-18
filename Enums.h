#pragma once
// 保持CharacterState 与 effectState 一致，有强转int对齐
enum class CharacterState {
	Default, KI_before, KI_after, KI_miss, I_before, I_after, I_miss, Stand, WI_before, Landed,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U, U_after, WUU, SUU,
	Running, Jumping, Fall, Hit, Kick, J1, J2, J3, J4, KJ, KU, KU_down, WJ, S,
	SJ, Flash, S_Release
};
enum class CharacterType {
	Default,
	Gaara,
	NarutoS,
};
enum class EffectState {
	Default, KI_before, KI_after, KI_miss, I_before, I_after, I_miss, Stand, WI_before, Landed,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U, U_after, WUU, SUU,
	Running, Jumping, Fall, Hit, Kick, J1, J2, J3, J4, KJ, KU, KU_down, WJ, S,
	SJ, Flash, S_Release,

	Flash_air, Flash_ash, Landed_ash, I_effect
};

enum class GameState {
	Init, SelectCharacter, SelectMap, Start, Playing, Over
};
// 开场界面(单次点击后出现开始游戏按钮)、选人、选地图、双方人物开场动画、正式游戏、一方死亡结束(播放win动画)

enum class EventType { // 事件队列，用于震屏
	SkillHit,
	FallImpact,
	UltimateSkill,    // 释放大招
	PauseRequest      // 暂停请求
};

struct PauseEvent {
	EventType type;       // 事件类型
	void* source;             // 事件触发源，例如角色指针
	float duration;           // 暂停持续时间（针对 PauseRequest）
	bool excludeSource;       // 是否排除触发源
};

