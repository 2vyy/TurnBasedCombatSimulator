#include "combat_logger.h"
#include <fmt/core.h>

void Combat_Logger::log_init(Team& team1, Team& team2) { //these should probably be const
	fmt::print("=== Combat Initialized ===\n"
	"Team [{}] ({} members)\n", team1.get_name_ref(), team1.get_size());
	for (auto& character : team1.get_characters()) {
		fmt::print(" - {} ({} HP, {} ATK, {} SPD)\n", character.get_name_ref(), character.get_health(), character.get_attack(), character.get_speed());
	}

	fmt::print("\nTeam [{}] ({} members)\n", team2.get_name_ref(), team2.get_size());
	for (auto& character : team2.get_characters()) {
		fmt::print(" - {} ({} HP, {} ATK, {} SPD)\n", character.get_name_ref(), character.get_health(), character.get_attack(), character.get_speed());
	}
}


void Combat_Logger::log_turn(const Character& actor, const Team& actor_team, const Character& target, const Team& target_team, int turn_count) {
	fmt::print("\n=== Turn {} ===\n"
		"{} [{}] (HP: {}/{})\n"
		" - Attacked [{}] for {} DMG\n"
		" - Target HP {} -> {}\n",
		turn_count,
		actor.get_name_ref(),
		actor_team.get_name_ref(),
		actor.get_health(),
		actor.get_max_health(),
		target.get_name_ref(),
		actor.get_attack(),
		target.get_health(),
		std::max(target.get_health() - actor.get_attack(), 0));
}

void Combat_Logger::log_death(const Character& character, const Team& character_team) {
	fmt::print("\n{} [{}] has died\n", character.get_name_ref(), character_team.get_name_ref());
}

void Combat_Logger::log_end(Team& team1, Team& team2, const int turn_count) {
	Team& winning_team = team1.is_defeated() ? team2 : team1;
	Team& losing_team = team1.is_defeated() ? team1 : team2;

	fmt::print("\n=== Combat Summary ===\n"
		"Victor: {} ({} survivors)\n"
		"Duration: {} turns\n\n"
		"Team [{}]:\n",
		winning_team.get_name_ref(),
		winning_team.get_alive_count(),
		turn_count,
		winning_team.get_name_ref());

	for (auto& character : winning_team.get_characters()) {
		fmt::print(" - {}: {}/{} HP\n",
			character.get_name_ref(), 
			character.get_health(),
			character.get_max_health());
	}

	// is it really necessary to print the losing team?
	fmt::print("Team [{}]:\n",
		losing_team.get_name_ref());

	for (auto& character : losing_team.get_characters()) {
		fmt::print(" - {}: 0/{} HP\n",
			character.get_name_ref(),
			character.get_max_health());
	}
}

void Combat_Logger::log_effect_apply(const Character& character, const Effect& effect) {
	fmt::print("\n{} has been applied with {}\n", character.get_name_ref(), effect.get_name());
}


// TODO: need to rework to be more generic (probably need to store text in the effect itself tbh)
void Combat_Logger::log_effect_tick(const Character& character, const Effect& effect, const int old_value, const int new_value) {
	fmt::print("\n{}'s {} modifies {} by {}\n"
			   "{} -> {}\n",
		character.get_name_ref(),
		effect.get_name(),
		effect.get_modifer(),
		effect.get_modifer_value(),
		old_value,
		new_value);
}

void Combat_Logger::log_effect_expire(const Character& character, const Effect& effect) {
	fmt::print("\n{}'s {} has expired\n", character.get_name_ref(), effect.get_name());
}