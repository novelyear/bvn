#pragma once

enum class CharacterState {
	Default, KI, I_before, I_after, I_miss, Stand, WI_before,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U,
	Running, Jumping, Fall, Hit, Kick, J1, J2, J3, KJ, KU, WJ, S,
	SJ, Flash, S_Release
};
enum class CharacterType {
	Gaara,
	NarutoS,
};
enum class EffectState {
	Default, KI, I_before, I_after, I_miss, Stand, WI_before,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U,
	Running, Jumping, Fall, Hit, Kick, J1, J2, J3, KJ, KU, WJ, S,
	SJ, Flash, S_Release
};