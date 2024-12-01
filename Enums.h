#pragma once

enum class CharacterState {
	Default, Stand, Running, Jumping, Fall, Hit, Kick, J1, J2, J3, U, KJ, KU, KI, I_before, I_after,
	I_miss, WI_before, WI_after, WI_miss, WU, WJ, S, SI_before, SI_after, SI_miss, SJ, SU, Flash, S_Release
};
enum class CharacterType {
	Gaara,
	NarutoS,
};
enum class EffectState {
	Default, KI, I_before, I_after, I_miss, WI_before,
	WI_after, WI_miss, SI_before, SI_after, SI_miss, SU, WU, U
};