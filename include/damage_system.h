#pragma once
#include "character.h"

namespace DamageSystem {

	//this is the outgoing struct for any instance of damage, mainly for logging purposes
	struct DamageResult {
		int base_damage;
		int outgoing_damage;
		int final_damage;

		bool is_crit;
		bool is_blocked;
		bool is_dodged;

		float crit_multiplier;

		int flat_armor_reduction;
		float armor_reduction_multiplier;

		std::vector<std::string> effect_messages;
	};

	// TODO: this should probably be put in constants
	struct DamageSettings {
		float base_crit_chance = 0.05f;
		float base_crit_multiplier = 1.5f;
	};

	//TODO: please standardize the naming scheme
	DamageResult calculate_damage(const Character& attacker, const Character& defender, const DamageSettings& settings);
}