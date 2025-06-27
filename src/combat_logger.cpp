#include "combat_logger.h"
#include <iostream>
#include <fmt/core.h>

void Combat_Logger::log_init(Team& team1, Team& team2) { //these should probably be const
	fmt::print("=== Combat Initialized ===\n"
	"Team [{}] ({} members)\n", team1.get_name_ref(), team1.get_size());
	for (auto& character : team1.get_characters()) {
		Character::CharacterStats stats = character.get_stats_ref();
		fmt::print(" - {} ({} HP, {} ATK, {} SPD)\n", character.get_name_ref(), stats.max_health, stats.attack, stats.speed);
	}

	fmt::print("\nTeam [{}] ({} members)\n", team2.get_name_ref(), team2.get_size());
	for (auto& character : team2.get_characters()) {
		Character::CharacterStats stats = character.get_stats_ref();
		fmt::print(" - {} ({} HP, {} ATK, {} SPD)\n", character.get_name_ref(), stats.max_health, stats.attack, stats.speed);
	}
}


// TODO: will need to be reworked to include damage system
void Combat_Logger::log_attack(const CombatEventContext& context, const DamageSystem::DamageResult result) {
	Character::CharacterStats attacker_stats = context.attacker.get_stats_ref();
	Character::CharacterStats defender_stats = context.defender.get_stats_ref();

	// TODO: need to include damage calculation here, as well as messages for blocking
	fmt::print("\n=== Turn {} ===\n"
		"{} [{}] (HP: {}/{})\n"
		" - Attacked [{}] for {} DMG\n"
		" - Target HP {} -> {}\n",
		context.turn_count,
		context.attacker.get_name_ref(),
		context.attacker_team.get_name_ref(),
		attacker_stats.curr_health,
		attacker_stats.max_health,
		context.defender.get_name_ref(),
		result.final_damage,
		defender_stats.curr_health,
		std::max(defender_stats.curr_health - attacker_stats.attack, 0));
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
		Character::CharacterStats stats = character.get_stats_ref();

		fmt::print(" - {}: {}/{} HP\n",
			character.get_name_ref(), 
			stats.curr_health,
			stats.max_health);
	}

	// is it really necessary to print the losing team?
	fmt::print("Team [{}]:\n",
		losing_team.get_name_ref());

	for (auto& character : losing_team.get_characters()) {
		Character::CharacterStats stats = character.get_stats_ref();

		fmt::print(" - {}: 0/{} HP\n",
			character.get_name_ref(),
			stats.max_health);
	}
}

void Combat_Logger::log_effect_apply(const Character& character, const Effect& effect) {
	fmt::print("\n{} has been applied with {}\n", character.get_name_ref(), effect.get_name());
}


void Combat_Logger::log_effect_tick(const std::string_view message) {
	std::cout << (message) << std::endl;
}

void Combat_Logger::log_effect_expire(const Character& character, const Effect& effect) {
	fmt::print("\n{}'s {} has expired\n", character.get_name_ref(), effect.get_name());
}