#pragma once
#include "team.h"
#include "effects/effect.h"

class Combat_Logger {
	public:
		static void log_init(Team& team1, Team& team2);
		static void log_turn(const Character& actor, const Team& actor_team, const Character& target, const Team& target_team, int turn_count);
		static void log_death(const Character& character, const Team& character_team);
		static void log_end(Team& team1, Team& team2, const int turn_count);

		static void log_effect_apply(const Character& character, const Effect& effect);
		static void log_effect_tick(const Character& character, const Effect& effect, const int old_value, const int new_value);
		static void log_effect_expire(const Character& character, const Effect& effect);

};