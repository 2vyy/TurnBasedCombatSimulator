#pragma once
#include "team.h"
#include "damage_system.h"
#include "combat_system.h"
#include "effect.h"

class Combat_Logger {
	public:
		static void log_init(Team& team1, Team& team2);
		static void log_attack(const CombatEventContext& context, const DamageSystem::DamageResult result);
		static void log_death(const Character& character, const Team& character_team);
		static void log_end(Team& team1, Team& team2, const int turn_count);
		static void log_cancel(const Character& character);

		static void log_effect_apply(const Character& character, const Effect& effect);
		static void log_effect_tick(const std::string_view message);
		static void log_effect_expire(const Character& character, const Effect& effect);

};