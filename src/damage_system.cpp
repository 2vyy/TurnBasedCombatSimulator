#include "damage_system.h"
#include "random.h"

namespace DamageSystem {
	DamageResult calculate_damage(const Character& attacker, const Character& defender, const DamageSettings& settings) {
		DamageResult result{};

		Character::CharacterStats attacker_stats = attacker.get_stats();
		Character::CharacterStats defender_stats = defender.get_stats();

		result.base_damage = attacker_stats.attack;
		result.outgoing_damage = result.base_damage;

		// blocking here
		
		// effects here

		if (Random::get(1,100) <= attacker_stats.crit_chance) {
			result.is_crit = true;
			result.outgoing_damage *= attacker_stats.crit_multiplier;
		}
		else {
			result.is_crit = false;
		}

		result.outgoing_damage = result.outgoing_damage * (1 - defender_stats.armor_percent) - defender_stats.armor;
	}
}

