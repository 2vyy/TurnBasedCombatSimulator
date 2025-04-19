#include "combat_logger.h"
#include <fmt/core.h>

void Combat_Logger::log_init(Team& team1, Team& team2) { //these should probably be const
	fmt::print("=== Combat Initialized ===\n"
	"Team [{}] ({} members)\n", team1.get_name_ref(), team1.get_size());
	for (auto& character : team1.get_characters()) {
		fmt::print(" - {} ({} HP, {} ATK, {} SPD)\n", character.get_name_ref(), character.get_health(), character.get_attack(), character.get_speed());
	}

	fmt::print("Team [{}] ({} members)\n", team2.get_name_ref(), team2.get_size());
	for (auto& character : team2.get_characters()) {
		fmt::print(" - {} ({} HP, {} ATK, {} SPD)\n", character.get_name_ref(), character.get_health(), character.get_attack(), character.get_speed());
	}

}