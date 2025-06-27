#pragma once
#include "character.h"


namespace DamageSystem {
	//this is the outgoing struct for any instance of damage, mainly for logging purposes
	struct DamageResult {
		int base_damage;
		int outgoing_damage;
		int final_damage;

		bool is_crit = false;

		float crit_multiplier = 1;

		int flat_armor_reduction = 0;
		float armor_reduction_multiplier = 0;

		std::vector<std::string> effect_messages;
	};

	// TODO: this should probably be put in constants
	struct DamageSettings {
		float base_crit_chance = 0.05f;
		float base_crit_multiplier = 1.5f;
	};

	//TODO: please standardize the naming scheme
	DamageResult calculate_damage(Character& attacker, Character& defender);
}