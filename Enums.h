#pragma once
// 保持CharacterState 与 effectState 一致，有强转int对齐
enum class CharacterState {
	Default, KI, I_before, I_after, I_miss, Stand, WI_before, Landed,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U, WUU, SUU,
	Running, Jumping, Fall, Hit, Kick, J1, J2, J3, J4, KJ, KU, WJ, S,
	SJ, Flash, S_Release
};
enum class CharacterType {
	Gaara,
	NarutoS,
};
enum class EffectState {
	Default, KI, I_before, I_after, I_miss, Stand, WI_before, Landed,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U, WUU, SUU,
	Running, Jumping, Fall, Hit, Kick, J1, J2, J3, J4, KJ, KU, WJ, S,
	SJ, Flash, S_Release
};

enum class GameState {
	Init, SelectCharacter, SelectMap, Start, Playing, Over
};